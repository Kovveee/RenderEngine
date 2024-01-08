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
		for(DirectionalLight* light: m_dirLights)
		{
			delete light;
		}
		m_editorGUI->destroyGui();

	}
	void Renderer::Init()
	{
		glfwWindowHint(GLFW_SAMPLES, 8);
		glEnable(GL_MULTISAMPLE);

		m_shaderProgram = new Shader(shaderFilePath + "vShader.vert", shaderFilePath + "fShader.frag");
		m_shaderProgram->BindUniformBlock(0, "Matrices");
		m_shaderProgram->BindUniformBlock(1, "Lights");
		

		m_matraciesUBO.SetBufferData(3 * sizeof(glm::mat4), 0);
		m_lightsUBO.SetBufferData(DIRECTIONAL_LIGHT_UBO_SIZE + POINT_LIGHT_UBO_SIZE,1);
		
		m_dirLights.push_back(new DirectionalLight(DirectionalLight::Count++, glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 4.0f, 1.0f)));


		m_shaderProgram->useProgram();
		m_shaderProgram->setMaterial(glm::vec3(1.0f, 0.5f, 1.f), glm::vec3(1.0f, 0.5f, 1.f), glm::vec3(0.5f, 0.5f, 0.5f), 32.f);
		m_shaderProgram->unuseProgram();

		m_editorGUI = new EditorGUI(m_window);

		camera = new EditorCamera(glm::vec3(0.f, 0.f, 3.0f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));

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

		InitShadowMap();

	}
	void Renderer::Render()
	{
		GenerateShadowMap();

		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glfwGetFramebufferSize(m_window, &m_screenWidth, &m_screenHeight);
		glViewport(0, 0, m_screenWidth, m_screenHeight);


		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;

		camera->Update(m_window, m_deltaTime);
		
		SetViewProjUBO();
		SetLightUBO();


		m_shaderProgram->useProgram();
		m_shaderProgram->setUniform("pointLightNum", PointLight::Count);
		m_shaderProgram->setUniform("dirLightNum", DirectionalLight::Count);
		m_shaderProgram->setUniform("shadowMap",3);
		m_shaderProgram->initUniformVariable("normalIsSet");
		m_shaderProgram->setUniform("normalIsSet", isNormalSet);
		m_shaderProgram->unuseProgram();

		//m_skybox->Draw();
		for (Model* model : m_models) {
			model->Draw(m_shaderProgram, camera->GetPos());
		}

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		RenderShadowMap();

		m_editorGUI->enableGui();
		m_editorGUI->MainWindow(m_models, m_dirLights);
		m_editorGUI->TestDepthMap(near_plane, far_plane, size, isNormalSet);
		m_editorGUI->drawGui();
	}
	void Renderer::SetLightUBO()
	{
		for (int i = 0; i < m_dirLights.size(); ++i)
		{
			m_lightsUBO.Bind();
			DirectionalLightData* data = (DirectionalLightData*)m_dirLights[i]->GetData();
			m_lightsUBO.SetUniform(i * DirectionalLight::Size, sizeof(glm::vec4), glm::value_ptr(data->direction));
			m_lightsUBO.SetUniform(i * DirectionalLight::Size + sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(data->ambient));
			m_lightsUBO.SetUniform(i * DirectionalLight::Size + sizeof(glm::vec4) * 2, sizeof(glm::vec4), glm::value_ptr(data->diffuse));
			m_lightsUBO.SetUniform(i * DirectionalLight::Size + sizeof(glm::vec4) * 3, sizeof(glm::vec4), glm::value_ptr(data->specular));
			m_lightsUBO.UnBind();
		}
		for(int i = 0; i < m_pointLights.size(); ++i)
		{
			m_lightsUBO.Bind();
			PointLightData* data = (PointLightData*)m_pointLights[i]->GetData();
			m_lightsUBO.SetUniform(DIRECTIONAL_LIGHT_UBO_SIZE + i * PointLight::Size, sizeof(glm::vec4), glm::value_ptr(data->position));
			m_lightsUBO.SetUniform(DIRECTIONAL_LIGHT_UBO_SIZE + i * PointLight::Size + sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(data->ambient));
			m_lightsUBO.SetUniform(DIRECTIONAL_LIGHT_UBO_SIZE + i * PointLight::Size + sizeof(glm::vec4) * 2, sizeof(glm::vec4), glm::value_ptr(data->diffuse));
			m_lightsUBO.SetUniform(DIRECTIONAL_LIGHT_UBO_SIZE + i * PointLight::Size + sizeof(glm::vec4) * 3, sizeof(glm::vec4), glm::value_ptr(data->specular));
			m_lightsUBO.SetUniform(DIRECTIONAL_LIGHT_UBO_SIZE + i * PointLight::Size + sizeof(glm::vec4) * 4, sizeof(float), &data->constant);
			m_lightsUBO.SetUniform(DIRECTIONAL_LIGHT_UBO_SIZE + i * PointLight::Size + sizeof(glm::vec4) * 4 + sizeof(float), sizeof(float), &data->linear);
			m_lightsUBO.SetUniform(DIRECTIONAL_LIGHT_UBO_SIZE + i * PointLight::Size + sizeof(glm::vec4) * 3 + sizeof(float) * 2, sizeof(float), &data->quadratic);
			m_lightsUBO.UnBind();
		}
	}
	void Renderer::SetViewProjUBO()
	{
		m_matraciesUBO.Bind();
		glm::mat4 tmpProj = glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, NEAR_PLANE, FAR_PLANE);
		m_matraciesUBO.SetUniform(0, sizeof(glm::mat4), glm::value_ptr(tmpProj));
		glm::mat4 tmpCameraView = camera->GetLookAt();
		m_matraciesUBO.SetUniform(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(tmpCameraView));
		m_matraciesUBO.SetUniform(sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(lightSpaceMatrix));
		m_matraciesUBO.UnBind();
	}
	void Renderer::InitShadowMap() {
		
	}
	void Renderer::GenerateShadowMap() {

		if(depthMapFBO == 0)
			glGenFramebuffers(1, &depthMapFBO);

		if(depthMap == 0)
			glGenTextures(1, &depthMap);
		// Creating the texture
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 4096, 4096, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glBindFramebuffer(GL_FRAMEBUFFER,depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
	
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Frambuffer is not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Renderer::RenderShadowMap() {
		glViewport(0, 0, 4096, 4096);
		glCullFace(GL_FRONT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 1.0);
		
		// ConfigureShaderAndMatrices
		glm::mat4 lightProjection = glm::ortho(-size, size, -size, size, near_plane, far_plane);

		DirectionalLightData* dirLightData = (DirectionalLightData*)m_dirLights[0]->GetData();
		if (dirLightData->direction.x == 0)
			dirLightData->direction.x = 0.01;
		if (dirLightData->direction.y == 0)
			dirLightData->direction.y = 0.01;
		if (dirLightData->direction.z == 0)
			dirLightData->direction.z = 0.01;

		glm::mat4 lightView = glm::lookAt(glm::vec3(dirLightData->direction.x, dirLightData->direction.y, dirLightData->direction.z), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.0f, 0.0f));

		lightSpaceMatrix = lightProjection * lightView;

		m_shadowMapShader = new Shader(shaderFilePath + "shadowMap.vert", shaderFilePath + "shadowMap.frag");

		// Render Scene
		m_shadowMapShader->useProgram();
		m_shadowMapShader->initUniformVariable("lightSpaceMatrix");
		m_shadowMapShader->setUniform("lightSpaceMatrix", lightSpaceMatrix);
		m_shadowMapShader->unuseProgram();

		for (Model* model : m_models) {
			model->Draw(m_shadowMapShader, camera->GetPos());
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, m_screenWidth, m_screenHeight);
		glPolygonOffset(0.0, 0.0);


		/*Vertex quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			{glm::vec3(-1.0f,1.0f,0.0f), glm::vec3(0.f,0.f,0.f) ,glm::vec2(0.0f, 1.0f)},
			{glm::vec3(-1.0f,-1.0f,0.0f), glm::vec3(0.f,0.f,0.f) ,glm::vec2(0.0f, 0.0f)},
			{glm::vec3(1.0f,-1.0f,0.0f), glm::vec3(0.f,0.f,0.f) ,glm::vec2(1.0f, 0.0f)},

			{glm::vec3(-1.0f,1.0f,0.0f), glm::vec3(0.f,0.f,0.f) ,glm::vec2(0.0f, 1.0f)},
			{glm::vec3(1.0f,1.0f,0.0f), glm::vec3(0.f,0.f,0.f) ,glm::vec2(1.0f, 1.0f)},
			{glm::vec3(1.0f,-1.0f,0.0f), glm::vec3(0.f,0.f,0.f) ,glm::vec2(1.0f, 0.0f)}
		};

		unsigned int indices[] = {
			0,1,2,
			3,4,5
		};

		VertexArray quadVao;
		VertexBuffer quadVbo;
		ElementBuffer quadIbo;

		m_shadowDebugShader = new Shader(shaderFilePath + "shadowMapDebug.vert", shaderFilePath + "shadowMapDebug.frag");
		m_shadowDebugShader->initUniformVariable("depthMap");
		m_shadowDebugShader->initUniformVariable("near_plane");
		m_shadowDebugShader->initUniformVariable("far_plane");

		quadVao.bind();
		quadVbo.setBufferData(6, quadVertices);
		quadVbo.bind();
		quadIbo.SetBufferData(6, indices);
		quadIbo.Bind();
		quadVao.initVertexArray();
		quadVao.unbind();
		quadIbo.Unbind();
		quadVbo.unbind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		glViewport(0, 0, m_screenWidth, m_screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shadowDebugShader->useProgram();
		m_shadowDebugShader->setUniform("near_plane", NEAR_PLANE);
		m_shadowDebugShader->setUniform("far_plane", 1000.f);
		m_shadowDebugShader->setUniform("depthMap", 0);
		quadVao.bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
		quadVao.unbind();
		m_shadowDebugShader->unuseProgram();*/
	}
}