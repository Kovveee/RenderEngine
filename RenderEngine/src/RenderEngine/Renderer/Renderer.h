#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "Camera.h"


namespace RenderEngine 
{

	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		void Init();
		void Render();
		void InitCube();
		void DrawCube(glm::mat4 worldMat, Shader* shader);
		void KeyboardInputHandler();
		void MouseInputHandler();

	private:
		GLFWwindow* m_window;

		Shader* shaderProgram;
		Shader* lightShaderProgram;

		const float screenWidth = 800.f;
		const float screenHeight = 600.f;

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		glm::mat4 cubeWorld = glm::mat4(1.f);
		glm::mat4 lightWorld = glm::mat4(1.f);

		glm::vec3 lightPos = glm::vec3(5.f, 6.f, -4.f);

		VertexArray* cubeVao;
		VertexBuffer* cubeVbo;
		ElementBuffer* cubeIbo;
		
		
		Camera* camera;

		float deltaTime = 0;
		float lastFrame = 0;

	};
}

