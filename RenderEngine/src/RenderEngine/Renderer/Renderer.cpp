#include "Renderer.h"

namespace RenderEngine
{
	Renderer::Renderer(GLFWwindow *window, float screenWidth, float screenHeight)
		: m_window(window),m_screenWidth(screenWidth), m_screenHeight(screenHeight)
	{
		// Init imGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		camera = nullptr;
		m_texture = nullptr;
		shaderProgram = nullptr;
		lightShaderProgram = nullptr;
		Init();

		
	}

	Renderer::~Renderer()
	{
		delete m_window;
		delete shaderProgram;
		delete lightShaderProgram;
		delete camera;
	}


	void Renderer::InitCube()
	{
		Vertex vertices[] =
		{
			{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.f, 1.f), glm::vec2(0.f, 1.f)}, //0
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.f, 1.f), glm::vec2(0.f, 0.f)},//1
			{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.f, 1.f), glm::vec2(1.f, 1.f)}, //2
			{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.f, 1.f), glm::vec2(1.f, 0.f)}, //3
		};

		const unsigned int indices[] =
		{
			0,1,3,
			3,2,0
		};

		cubeVao = new VertexArray();
		cubeVao->Bind();

		cubeVbo.SetBufferData(4, vertices);
		cubeVbo.Bind();

		cubeIbo.SetBufferData(6, indices);
		cubeIbo.Bind();

		cubeVao->InitVertexArray();

		cubeVao->Unbind();
		cubeIbo.Unbind();
		cubeVbo.Unbind();



	}
	void Renderer::DrawCube(glm::mat4 worldMat, Shader* shader) 
	{
		cubeVao->Bind();
		shader->UseProgram();
		m_texture->Bind();
		
		shader->setUniform("objectColor", m_cubeColor);
		shader->InitUniformVariable("ourTexture");
		shader->setUniform("ourTexture", 0);
		shader->setUniform("cameraPos", camera->GetPos());
		shader->setLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), lightPos);
		
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
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			angle += 90;
		}

		tempCubeWorld = worldMat;
		tempCubeWorld *= glm::translate(glm::vec3(0.f, -0.5f, 0.f)) * glm::rotate<float>(glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
		shader->setWVP(tempCubeWorld, view, projection);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		tempCubeWorld = worldMat;
		tempCubeWorld *= glm::translate(glm::vec3(0.f, 0.5f, 0.f)) * glm::rotate<float>(glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
		shader->setWVP(tempCubeWorld, view, projection);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		m_texture->UnBind();
		shader->UnuseProgram();
		cubeVao->Unbind();
	}
	
	void Renderer::Init()
	{
		shaderProgram = new Shader(shaderFilePath + "vShader.vert", shaderFilePath + "fShader.frag");
		lightShaderProgram = new Shader(shaderFilePath + "lightShader.vert", shaderFilePath + "lightShader.frag");
		modelShader = new Shader(shaderFilePath + "modelLoading.vert", shaderFilePath + "modelLoading.frag");

		m_texture = new Texture(textureFolderPath + "container.jpg","normal");

		projection = glm::perspective(glm::radians(45.f), m_screenWidth / m_screenHeight, 0.1f, 100.f);
		
		//model = new Model("src\\Models\\cube\\untitled.obj");
		backpack = new Model("src\\Models\\spacemarine\\space_marine.obj");

		InitCube();
		shaderProgram->UseProgram();
		shaderProgram->setMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.f);
		shaderProgram->UnuseProgram();

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

			//DrawCube(cubeWorld, shaderProgram);
			DrawCube(lightWorld, lightShaderProgram);
			//model->Draw(shaderProgram, cubeWorld, view, projection, camera->GetPos(), m_cubeColor);
			backpack->Draw(shaderProgram, glm::translate(glm::vec3(0.f, -6.f, 0.f)), view, projection, camera->GetPos(), m_cubeColor);

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