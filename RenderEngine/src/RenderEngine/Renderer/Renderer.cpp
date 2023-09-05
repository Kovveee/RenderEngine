#include "Renderer.h"

namespace RenderEngine
{
	Renderer::Renderer(GLFWwindow *window, int screenWidth, int screenHeight, std::vector<Model*> &models)
		: m_window(window),m_screenWidth(screenWidth), m_screenHeight(screenHeight), m_models(models)
	{
		camera = nullptr;
		m_shaderProgram = nullptr;
		Init();	
	}

	Renderer::~Renderer()
	{
		delete m_shaderProgram;
		delete camera;
		for(Model* model: m_models)
		{
			delete model;
		}
		for(LightSource* light: m_lights)
		{
			delete light;
		}
		m_editorGUI->destroyGui();

	}
	void Renderer::Init()
	{
		m_shaderProgram = new Shader(shaderFilePath + "vShader.vert", shaderFilePath + "fShader.frag");
		m_shaderProgram->BindUniformBlock(0, "Matrices");
		m_outlineShader = new Shader(shaderFilePath + "vShader.vert", shaderFilePath + "outline.frag");
		m_outlineShader->BindUniformBlock(0, "Matrices");
		m_planeShader = new Shader(shaderFilePath + "vShader.vert", shaderFilePath + "planeColor.frag");

		m_matraciesUBO.SetBufferData(2 * sizeof(glm::mat4), 0);


		m_outlineShader->useProgram();
		m_outlineShader->initUniformVariable("color");
		m_outlineShader->unuseProgram();
		
		m_lights.push_back(new PointLight(m_pointLightNum++, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 5.f)));
		m_lights.push_back(new DirectionalLight(m_dirLightNum++, glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, -5.f, 0.f)));

		m_shaderProgram->useProgram();
		m_shaderProgram->setMaterial(glm::vec3(1.0f, 0.5f, 1.f), glm::vec3(1.0f, 0.5f, 1.f), glm::vec3(0.5f, 0.5f, 0.5f), 32.f);
		m_shaderProgram->unuseProgram();

		m_editorGUI = new EditorGUI(m_window);

		camera = new EditorCamera(glm::vec3(0.f, 0.f, 3.0f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
		gameCamera = new GameCamera();

		m_lastFpsFrame = glfwGetTime();

		std::vector<std::string> skyboxTextures =
		{
			textureFolderPath + "skybox\\right.jpg",
			textureFolderPath + "skybox\\left.jpg",
			textureFolderPath + "skybox\\top.jpg",
			textureFolderPath + "skybox\\bottom.jpg",
			textureFolderPath + "skybox\\front.jpg",
			textureFolderPath + "skybox\\back.jpg"
		};
		m_skybox = new Skybox(skyboxTextures);
	}
	void Renderer::Render()
	{
		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glfwGetFramebufferSize(m_window, &m_screenWidth, &m_screenHeight);
		glViewport(0, 0, m_screenWidth, m_screenHeight);

		//GetFps();

		m_skybox->Draw(gameCamera->GetLookAt(), glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 150.f));

		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		//camera->Update(m_window, m_deltaTime);
		gameCamera->Update(m_deltaTime, m_models[0]);

		m_matraciesUBO.Bind();
		glm::mat4 tmpProj = glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 440.f);
		m_matraciesUBO.SetUniform(0, sizeof(glm::mat4), glm::value_ptr(tmpProj));
		glm::mat4 tmpCameraView = gameCamera->GetLookAt();
		m_matraciesUBO.SetUniform(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(tmpCameraView));
		m_matraciesUBO.UnBind();

		m_shaderProgram->useProgram();
		m_shaderProgram->setUniform("pointLightNum", m_pointLightNum);
		m_shaderProgram->setUniform("dirLightNum", m_dirLightNum);
		m_shaderProgram->unuseProgram();

		for (int i = 0; i < m_lights.size(); ++i)
		{
			m_lights[i]->SetInShader(m_shaderProgram);
		}
		for (Model* model : m_models) {
			model->Draw(m_shaderProgram, gameCamera->GetLookAt(), glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 440.f), gameCamera->GetPos());
		}

		KeyboardInputHandler();
		MouseInputHandler();

		m_editorGUI->enableGui();
		m_editorGUI->MainWindow(m_models);
		m_editorGUI->drawGui();
	}
	void Renderer::KeyboardInputHandler()
	{

	}
	void Renderer::MouseInputHandler()
	{

	}
	void Renderer::MagicCube(Model* cube, Model* plane)
	{
		m_planeShader->useProgram();
		m_planeShader->setUniform("color", glm::vec3(1, 1, 1));
		m_planeShader->unuseProgram();

		glDisable(GL_DEPTH_TEST);
		cube->Draw(m_planeShader, camera->GetLookAt(), glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 150.f), camera->GetPos());
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_STENCIL_TEST);
		glClear(GL_STENCIL_BUFFER_BIT);
		float angle = 0;

		
		for (int i = 0; i < 4; ++i)
		{
			glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
			glStencilFunc(GL_EQUAL, 0, 0xFF);
			glDisable(GL_DEPTH_TEST);
			glColorMask(0, 0, 0, 0);
			if(i == 0)
				*plane->GetTranslation() = glm::vec3(1, 0, 0);
			else if(i == 1)
				*plane->GetTranslation() = glm::vec3(0, 0, -1);
			else if (i == 2)
				*plane->GetTranslation() = glm::vec3(-1, 0, 0);
			else if (i == 3)
				*plane->GetTranslation() = glm::vec3(0, 0, 1);
			*plane->GetScale() = glm::vec3(0.7, 0.7, 0.7);
			*plane->GetRotation() = glm::vec3(0, angle, 0);
			angle += 90;
			if (angle == 360)
				angle = 0;
			plane->Draw(m_planeShader, camera->GetLookAt(), glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 150.f), camera->GetPos());
			glColorMask(1, 1, 1, 1);
			glEnable(GL_DEPTH_TEST);
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
			glStencilFunc(GL_EQUAL, 1, 0xFF);
			m_outlineShader->useProgram();
			m_outlineShader->setUniform("color", glm::vec3(1, 1, 0));
			m_outlineShader->unuseProgram();
			*m_models[i]->GetTranslation() = glm::vec3(0, 0, 0);
			*m_models[i]->GetScale() = glm::vec3(0.5, 0.5, 0.5);
			m_models[i]->Draw(m_outlineShader, camera->GetLookAt(), glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 150.f), camera->GetPos());
			*m_models[i]->GetScale() = glm::vec3(1, 1, 1);
			glClear(GL_STENCIL_BUFFER_BIT);
		}
		glDisable(GL_STENCIL_TEST);
	}
}