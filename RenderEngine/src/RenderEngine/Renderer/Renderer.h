#pragma once

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

// C++
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

// RenderEngine
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Model.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "LightSource.h"
#include "EditorCameraController.h"
#include "EditorGUI.h"
#include "Skybox.h"
#include "UniformBuffer.h"
#include "ShadowBox.h"

#define DIRECTIONAL_LIGHT_UBO_SIZE 4*10*sizeof(glm::vec4)
#define POINT_LIGHT_UBO_SIZE 10*(4 * sizeof(glm::vec4) + 3 * sizeof(float))

#define FAR_PLANE 1000.f
#define NEAR_PLANE 0.01f

namespace RenderEngine 
{
	class Renderer
	{
	public:
		Renderer(GLFWwindow* window, int screenWidth, int screenHeight, std::vector<Model*> &models);
		~Renderer();
		void Init();
		void Render();
	private:
		std::vector<Model*>& m_models;
		std::vector<DirectionalLight*> m_dirLights;
		std::vector<PointLight*> m_pointLights;

		// ShadowMapping
		unsigned int depthMapFBO = 0;
		unsigned int depthMap = 0;


		// Testing depth map
		float near_plane = 0.1f;
		float far_plane = 400.f;
		float size = 30.f;

		bool isNormalSet = false;


		glm::mat4 lightSpaceMatrix;

		int m_dirLightNum = 0;
		int m_pointLightNum = 0;

		GLFWwindow* m_window;

		EditorGUI* m_editorGUI;

		Shader* m_shaderProgram;
		Shader* m_outlineShader;
		Shader* m_planeShader;
		Shader* m_shadowMapShader;
		Shader* m_shadowDebugShader;

		Skybox* m_skybox;

		UniformBuffer m_matraciesUBO;
		UniformBuffer m_lightsUBO;

		int m_screenWidth;
		int m_screenHeight;

		Camera* camera;

		glm::mat4 m_projection = glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 150.f);

		const std::string shaderFilePath = "..\\..\\..\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\";
		const std::string textureFolderPath = "..\\..\\..\\Sandbox\\src\\Textures\\";

		float m_deltaTime = 0;
		float m_lastFrame = 0;

		// GUI variables
		glm::vec3 m_cubeColor = glm::vec3(1.f);
		float m_cubeRotationAngle = 0;
		float m_lastCubeRotationAngle = 0;
		bool m_rotateXEnable = false;
		bool m_rotateYEnable = false;
		bool m_rotateZEnable = false;

		// Private Methods
		void SetLightUBO();
		void SetViewProjUBO();

		void GenerateShadowMap();
		void RenderShadowMap();
	};
}

