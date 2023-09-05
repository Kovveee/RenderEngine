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
#include "EditorCamera.h"
#include "EditorGUI.h"
#include "GameCamera.h"
#include "Skybox.h"
#include "UniformBuffer.h"

namespace RenderEngine 
{

	class Renderer
	{
	public:
		Renderer(GLFWwindow* window, int screenWidth, int screenHeight, std::vector<Model*> &models);
		~Renderer();
		void Init();
		void Render();
		void KeyboardInputHandler();
		void MouseInputHandler();
	private:
		std::vector<Model*>& m_models;
		std::vector<LightSource*> m_lights;

		int m_dirLightNum = 0;
		int m_pointLightNum = 0;

		GLFWwindow* m_window;

		EditorGUI* m_editorGUI;

		Shader* m_shaderProgram;
		Shader* m_outlineShader;
		Shader* m_planeShader;

		Skybox* m_skybox;

		UniformBuffer m_matraciesUBO;

		glm::vec3 m_direction = glm::vec3(1,1,1);

		int m_screenWidth;
		int m_screenHeight;

		Camera* camera;
		GameCamera* gameCamera;		

		glm::mat4 m_projection = glm::perspective(glm::radians(45.f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 150.f);

		// GUI variables
		glm::vec3 m_cubeColor = glm::vec3(1.f);
		float m_cubeRotationAngle = 0;
		float m_lastCubeRotationAngle = 0;
		bool m_rotateXEnable = false;
		bool m_rotateYEnable = false;
		bool m_rotateZEnable = false;

		const std::string shaderFilePath = "..\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\";
		const std::string textureFolderPath = "src\\Textures\\";

	
		float m_deltaTime = 0;
		float m_lastFrame = 0;
		float m_lastFpsFrame = 0;
		void MagicCube(Model* cube, Model* plane);		

		float fps = 0;

		void GetFps()
		{	
			int numberOfFrames = 0;
			fps++;
			if(glfwGetTime() - m_lastFpsFrame >= 1.0)
			{
				std::cout << "FPS: " << fps << std::endl;
				fps = 0;
				m_lastFpsFrame += 1.0;
			}
		}
	};
}

