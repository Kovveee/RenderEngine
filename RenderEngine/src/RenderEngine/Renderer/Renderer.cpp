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

		m_window = glfwCreateWindow(screenWidth, screenHeight, "Hello World!", NULL, NULL);

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
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.f, 0.f), glm::vec2(0.f, 0.f)},
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.f, 0.f), glm::vec2(0.f, 0.f)},
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.f, 0.f), glm::vec2(0.f, 0.f)},
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.f, 0.f), glm::vec2(0.f, 0.f)}
		};

		const unsigned int indices[] =
		{
			0,1,3,
			3,2,0
		};

		cubeVao = new VertexArray();
		cubeVao->Bind();

		cubeVbo = new VertexBuffer(4, vertices);
		cubeVbo->Bind();

		cubeIbo = new ElementBuffer(6, indices);
		cubeIbo->Bind();

		cubeVao->InitVertexArray();

		cubeVao->Unbind();
		cubeIbo->Unbind();
		cubeVbo->Unbind();


		
	}
	void Renderer::DrawCube() {
		cubeVao->Bind();
		shaderProgram->UseProgram();
		glm::mat4 tempCubeWorld = cubeWorld;
		float angle = 0;
		for (int i = 0; i < 5; ++i) {
			tempCubeWorld = glm::rotate(tempCubeWorld,glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));
			shaderProgram->setWVP(tempCubeWorld, view, projection);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			angle += 90;
		}
		
		tempCubeWorld = cubeWorld;
		tempCubeWorld = glm::rotate(tempCubeWorld, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
		shaderProgram->setWVP(tempCubeWorld, view, projection);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		tempCubeWorld = cubeWorld;
		tempCubeWorld = glm::rotate(tempCubeWorld, glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
		shaderProgram->setWVP(tempCubeWorld, view, projection);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


		shaderProgram->UnuseProgram();
		cubeVao->Unbind();
	}

	void Renderer::Init()
	{
		Vertex vertices[] =
		{
			{glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(1.0f, 0.f, 0.f),	glm::vec2(0,0)},
			{glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.f, 1.0f, 0.f),	glm::vec2(0,0)},
			{glm::vec3(0.0f, 0.5f, 0.0f),		glm::vec3(0.f, 0.f, 1.0f),	glm::vec2(0,0)}
		};

		const unsigned int indices[] =
		{
			0,1,2
		};
		
		vao = new VertexArray();
		vao->Bind();

		vbo = new VertexBuffer(3, vertices);
		vbo->Bind();

		ibo = new ElementBuffer(3, indices);
		ibo->Bind();

		vao->InitVertexArray();

		
		vao->Unbind();
		vbo->Unbind();
		ibo->Unbind();

		shaderProgram = new Shader("C:\\dev\\RenderEngine\\RenderEngine\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\vShader.vert", "C:\\dev\\RenderEngine\\RenderEngine\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\fShader.frag");
		shaderProgram->InitUniformVariable("colorChange");


		triangleModel = glm::rotate(triangleModel, glm::radians(-55.0f), glm::vec3(1.f, 0.f, 0.f));
		view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
		projection = glm::perspective(glm::radians(45.f), screenWidth / screenHeight, 0.1f, 100.f);

		InitCube();

	}


	void Renderer::Render() 
	{
		while (!glfwWindowShouldClose(m_window)) 
		{
			glClearColor(0.2f, 0.4f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			DrawCube();

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

		glfwTerminate();

		return;
	}

}