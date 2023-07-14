#include "Renderer.h"

#include <iostream>



namespace RenderEngine
{
	Renderer::Renderer()
		: m_window(NULL)
	{
		if (!glfwInit())
			return;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(screenWidth, screenHeight, "Main Window", NULL, NULL);

		if (!m_window) {
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);

		glfwSwapInterval(1);

		if (GLEW_OK != glewInit())
			return;
		Init();
	}

	Renderer::~Renderer()
	{

	}


	void Renderer::InitCube()
	{
		Vertex vertices[] =
		{
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.f, 1.f), glm::vec2(0.f, 0.f)}, //0
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.f, 1.f), glm::vec2(0.f, 0.f)},//1
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.f, 1.f), glm::vec2(0.f, 0.f)}, //2
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.f, 1.f), glm::vec2(0.f, 0.f)}, //3
		};

		const unsigned int indices[] =
		{
			0,1,3,
			3,2,0
		};

		cubeVao = new VertexArray();
		cubeVao->Bind();

		cubeVbo = new VertexBuffer(8, vertices);
		cubeVbo->Bind();

		cubeIbo = new ElementBuffer(36, indices);
		cubeIbo->Bind();

		cubeVao->InitVertexArray();

		cubeVao->Unbind();
		cubeIbo->Unbind();
		cubeVbo->Unbind();



	}
	void Renderer::DrawCube(glm::mat4 worldMat, Shader* shader) {
		cubeVao->Bind();
		shader->UseProgram();
		glm::mat4 tempCubeWorld;
		glm::vec3 pos;
		float angle = 0;
		for (int i = 0; i < 4; ++i) {
			if (i == 0)
				pos = glm::vec3(0.f, 0.f, 0.5f);
			else if(i == 1)
				pos = glm::vec3(0.5f, 0.f, 0.f);
			else if (i == 2)
				pos = glm::vec3(0.f, 0.f, -0.5f);
			else if (i == 3)
				pos = glm::vec3(-0.5f, 0.f, 0.f);
			tempCubeWorld = worldMat;
			tempCubeWorld *= glm::translate(pos) * glm::rotate<float>(glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));
			shaderProgram->setWVP(tempCubeWorld, view, projection);
			shaderProgram->setUniform("worldIT", glm::inverse(glm::transpose(tempCubeWorld)));
			shaderProgram->setUniform("lightPos", lightPos);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			angle += 90;
		}

		tempCubeWorld = worldMat;
		tempCubeWorld *= glm::translate(glm::vec3(0.f, -0.5f, 0.f)) * glm::rotate<float>(glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
		shaderProgram->setWVP(tempCubeWorld, view, projection);
		shaderProgram->setUniform("worldIT", glm::inverse(glm::transpose(tempCubeWorld)));
		shaderProgram->setUniform("lightPos", lightPos);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		tempCubeWorld = worldMat;
		tempCubeWorld *= glm::translate(glm::vec3(0.f, 0.5f, 0.f)) * glm::rotate<float>(glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
		shaderProgram->setWVP(tempCubeWorld, view, projection);
		shaderProgram->setUniform("worldIT", glm::inverse(glm::transpose(tempCubeWorld)));
		shaderProgram->setUniform("lightPos", lightPos);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


		shader->UnuseProgram();
		cubeVao->Unbind();
	}

	void Renderer::Init()
	{
		shaderProgram = new Shader("C:\\dev\\RenderEngine\\RenderEngine\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\vShader.vert", "C:\\dev\\RenderEngine\\RenderEngine\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\fShader.frag");
		shaderProgram->UseProgram();
		shaderProgram->InitUniformVariable("objectColor");
		shaderProgram->setUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shaderProgram->InitUniformVariable("lightColor");
		shaderProgram->setUniform("lightColor", glm::vec3(1.0f, 1.f, 1.f));
		shaderProgram->UnuseProgram();

		lightShaderProgram = new Shader("C:\\dev\\RenderEngine\\RenderEngine\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\lightShader.vert", "C:\\dev\\RenderEngine\\RenderEngine\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\lightShader.frag");


		projection = glm::perspective(glm::radians(45.f), screenWidth / screenHeight, 0.1f, 100.f);

		InitCube();

		camera = new Camera(glm::vec3(0.f, 0.f, 3.0f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));

		lightWorld *= glm::translate(lightPos) * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	}


	void Renderer::Render()
	{
		while (!glfwWindowShouldClose(m_window))
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			camera->Update(m_window, deltaTime);

			view = camera->GetLookAt();

			DrawCube(cubeWorld, shaderProgram);
			DrawCube(lightWorld, lightShaderProgram);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
			KeyboardInputHandler();
			MouseInputHandler();
		}

		glfwTerminate();

		return;
	}
	void Renderer::KeyboardInputHandler()
	{
		
	}
	void Renderer::MouseInputHandler()
	{
	}
}