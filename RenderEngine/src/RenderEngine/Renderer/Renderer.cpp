#include "Renderer.h"

namespace RenderEngine
{
	Renderer::Renderer(GLFWwindow *window, int screenWidth, int screenHeight)
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
		shaderProgram = nullptr;
		lightShaderProgram = nullptr;
		Init();
		
	}

	Renderer::~Renderer()
	{
		delete shaderProgram;
		delete lightShaderProgram;
		delete camera;
		for(Model* model: m_models)
		{
			delete model;
		}
		for(LightSource* light: m_lights)
		{
			delete light;
		}
	}
	void Renderer::Init()
	{
		shaderProgram = new Shader(shaderFilePath + "vShader.vert", shaderFilePath + "fShader.frag");
		
		model = new Model("cube", "src\\Models\\cube\\untitled.obj");
		backpack = new Model("spacemarine", "src\\Models\\spacemarine\\space_marine.obj");

		pointLight = new PointLight(m_pointLightNum++, glm::vec3(0.5f, 0.f, 0.5f), glm::vec3(0.8f, 0.f, 0.8f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f));
		directional = new DirectionalLight(m_dirLightNum, glm::vec3(0.f, 0.1f, 0.4f), glm::vec3(0.f, 0.2f, 0.8f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 15.f));
		m_dirLightNum++;
		directional2 = new DirectionalLight(m_dirLightNum++, glm::vec3(0.2f, 0.2f, 0.f), glm::vec3(5.f, 0.3f, 0.0), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, -15.f));

		m_lights.push_back(directional);
		m_lights.push_back(directional2);
		m_lights.push_back(pointLight);


		m_models.push_back(model);
		m_models.push_back(backpack);

		shaderProgram->UseProgram();
		shaderProgram->setMaterial(glm::vec3(1.0f, 0.5f, 1.f), glm::vec3(1.0f, 0.5f, 1.f), glm::vec3(0.5f, 0.5f, 0.5f), 32.f);
		shaderProgram->UnuseProgram();
		projection = glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 150.f);


		camera = new Camera(glm::vec3(0.f, 0.f, 3.0f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
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

			glfwGetFramebufferSize(m_window, &m_screenWidth, &m_screenHeight);
			glViewport(0, 0, m_screenWidth, m_screenHeight);
			projection = glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 150.f);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		
			

			MainWindow();

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			camera->Update(m_window, deltaTime);

			view = camera->GetLookAt();


			shaderProgram->UseProgram();
			shaderProgram->setUniform("pointLightNum", m_pointLightNum);
			shaderProgram->setUniform("dirLightNum", m_dirLightNum);
			shaderProgram->UnuseProgram();

			for(int i = 0; i < m_lights.size(); ++i)
			{
				m_lights[i]->SetInShader(shaderProgram);
			}
			for(int i = 0; i < m_models.size();++i)
			{
				m_models[i]->Draw(shaderProgram, view, projection, camera->GetPos());
			}

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

	void Renderer::MainWindow()
	{
		ImGui::Begin("Main window");
		static int item_current_idx = 0;
		if (ImGui::BeginListBox("Objects"))
		{
			for (int n = 0; n < m_models.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(m_models[n]->GetName().c_str(), is_selected))
					item_current_idx = n;

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
					PropertyWindow(m_models[n]);
				}
					
			}
			ImGui::EndListBox();
		}
		ImGui::End();
	}
	void Renderer::PropertyWindow(Model* model)
	{
		ImGui::Begin((model->GetName() + " properties").c_str());
		ImGui::DragFloat3("Position", (float*)model->GetTranslation(), 1.f, -1000.f, 1000.f);
		ImGui::DragFloat3("Rotation", (float*)model->GetRotation(), 1.f, -360.f, 360.f);
		ImGui::DragFloat3("Scale", (float*)model->GetScale(), 0.001f, 0.001f, 1000.f);
		ImGui::End();
	}
}