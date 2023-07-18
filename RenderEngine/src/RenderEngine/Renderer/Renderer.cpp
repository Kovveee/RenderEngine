#include "Renderer.h"

namespace RenderEngine
{
	Renderer::Renderer()
		: m_window(NULL)
	{

		// Init openGL
		if (!glfwInit())
			return;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(screenWidth, screenHeight, "Main Window", NULL, NULL);

		if (!m_window) 
{
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);

		glfwSwapInterval(1);

		if (GLEW_OK != glewInit())
			return;

		// Init imGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		Init();
	}

	Renderer::~Renderer()
	{
		delete m_window;
		delete shaderProgram;
		delete lightShaderProgram;
		delete cubeVao;
		delete cubeIbo;
		delete cubeVbo;
		delete camera;
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
	void Renderer::DrawCube(glm::mat4 worldMat, Shader* shader) 
	{
		cubeVao->Bind();
		shader->UseProgram();
		shaderProgram->setUniform("objectColor", m_cubeColor);
		glm::mat4 tempCubeWorld;
		glm::vec3 pos;
		float angle = 0;
		for (int i = 0; i < 4; ++i) 
		{
			if (i == 0)
				pos = glm::vec3(0.f, 0.f, 0.5f);
			else if (i == 1)
				pos = glm::vec3(0.5f, 0.f, 0.f);
			else if (i == 2)
				pos = glm::vec3(0.f, 0.f, -0.5f);
			else if (i == 3)
				pos = glm::vec3(-0.5f, 0.f, 0.f);
			tempCubeWorld = worldMat;
			tempCubeWorld *= glm::translate(pos) * glm::rotate<float>(glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));
			shader->setWVP(tempCubeWorld, view, projection);
			shader->setUniform("lightPos", lightPos);
			shader->setUniform("cameraPos", camera->GetPos());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			angle += 90;
		}

		tempCubeWorld = worldMat;
		tempCubeWorld *= glm::translate(glm::vec3(0.f, -0.5f, 0.f)) * glm::rotate<float>(glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
		shader->setWVP(tempCubeWorld, view, projection);
		shader->setUniform("lightPos", lightPos);
		shader->setUniform("cameraPos", camera->GetPos());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		tempCubeWorld = worldMat;
		tempCubeWorld *= glm::translate(glm::vec3(0.f, 0.5f, 0.f)) * glm::rotate<float>(glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
		shader->setWVP(tempCubeWorld, view, projection);
		shader->setUniform("lightPos", lightPos);
		shader->setUniform("cameraPos", camera->GetPos());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);


		shader->UnuseProgram();
		cubeVao->Unbind();
	}
	
	void Renderer::Init()
	{
		shaderProgram = new Shader(shaderFilePath + "vShader.vert", shaderFilePath + "fShader.frag");


		lightShaderProgram = new Shader(shaderFilePath + "lightShader.vert", shaderFilePath + "lightShader.frag");


		projection = glm::perspective(glm::radians(45.f), screenWidth / screenHeight, 0.1f, 100.f);

		InitCube();

		camera = new Camera(glm::vec3(0.f, 0.f, 3.0f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));

		lightWorld *= glm::translate(lightPos) * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
	}
	void Renderer::Render()
	{
		while (!glfwWindowShouldClose(m_window))
		{
			glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glfwPollEvents();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			CreateGUI();

			shaderProgram->UseProgram();
			shaderProgram->InitUniformVariable("objectColor");
			shaderProgram->InitUniformVariable("lightColor");
			shaderProgram->setUniform("lightColor", glm::vec3(1.0f, 1.f, 1.f));
			shaderProgram->UnuseProgram();

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			camera->Update(m_window, deltaTime);

			view = camera->GetLookAt();

			glm::vec3 cubeAxis = glm::vec3(0.f);
			if (m_rotateXEnable)
				cubeAxis += glm::vec3(1.f, 0.f, 0.f);
			else if(cubeAxis.x != 0 && !m_rotateXEnable)
				cubeAxis += glm::vec3(-1.f, 0.f, 0.f);
			if (m_rotateYEnable)
				cubeAxis += glm::vec3(0.f, 1.f, 0.f);
			else if (cubeAxis.y != 0 && !m_rotateYEnable)
				cubeAxis += glm::vec3(0.f, -1.f, 0.f);
			if (m_rotateZEnable)
				cubeAxis += glm::vec3(0.f, 0.f, 1.f);
			else if (cubeAxis.z != 0 && !m_rotateZEnable)
				cubeAxis += glm::vec3(0.f, 0.f, -1.f);

			if(m_cubeRotationAngle != m_lastCubeRotationAngle && glm::vec3(0) != cubeAxis)
			{
				cubeWorld = glm::mat4(1.0) * glm::rotate<float>(glm::radians(m_cubeRotationAngle), cubeAxis);
				m_lastCubeRotationAngle = m_cubeRotationAngle;
			}

			DrawCube(cubeWorld, shaderProgram);
			DrawCube(lightWorld, lightShaderProgram);



			KeyboardInputHandler();
			MouseInputHandler();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(m_window);
		}

		glfwTerminate();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		return;
	}
	void Renderer::KeyboardInputHandler()
	{

	}
	void Renderer::MouseInputHandler()
	{
	}
	void Renderer::CreateGUI() 
	{
		ImGui::Begin("Main window");
		ImGui::SetWindowSize(ImVec2(300, 400));
		ImGui::ColorEdit3("Cube changer", (float*) & m_cubeColor);
		ImGui::SliderFloat("Rotation angle", &m_cubeRotationAngle, 0.f, 360.f);
		ImGui::Checkbox("RotationX", &m_rotateXEnable);
		ImGui::Checkbox("RotationY", &m_rotateYEnable);
		ImGui::Checkbox("RotationZ", &m_rotateZEnable);
		ImGui::End();
	}
}