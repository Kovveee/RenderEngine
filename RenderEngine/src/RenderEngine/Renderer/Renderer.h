#pragma once

//imGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

namespace RenderEngine 
{

	class Renderer
	{
	public:
		Renderer(GLFWwindow* window, int screenWidth, int screenHeight);
		~Renderer();
		void Init();
		void Render();
		void KeyboardInputHandler();
		void MouseInputHandler();
	private:
		std::vector<Model*> m_models;
		std::vector<LightSource*> m_lights;

		int m_dirLightNum = 0;
		int m_pointLightNum = 0;

		LightSource* pointLight;
		LightSource* directional;
		LightSource* directional2;

		VertexArray* cubeVao;

		Model* model;
		Model* backpack;

		GLFWwindow* m_window;

		Shader* shaderProgram;
		Shader* lightShaderProgram;
		Shader* modelShader;

		int m_screenWidth;
		int m_screenHeight;

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		glm::mat4 cubeWorld = glm::mat4(1.f);
		glm::mat4 lightWorld = glm::mat4(1.f);

		glm::vec3 lightPos = glm::vec3(-1.f, 3.f, 2.f);

		Camera* camera;

		


		// GUI variables
		glm::vec3 m_cubeColor = glm::vec3(1.f);
		float m_cubeRotationAngle = 0;
		float m_lastCubeRotationAngle = 0;
		bool m_rotateXEnable = false;
		bool m_rotateYEnable = false;
		bool m_rotateZEnable = false;

		const std::string shaderFilePath = "..\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\";
		const std::string textureFolderPath = "src\\Textures\\";

	
		float deltaTime = 0;
		float lastFrame = 0;

		void MainWindow();
		void PropertyWindow(Model* model);
		
	};
}

