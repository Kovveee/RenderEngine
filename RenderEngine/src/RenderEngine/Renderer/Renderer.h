#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include <string>
#include <glm/glm.hpp>


namespace RenderEngine 
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		void Init();
		void Render();

	private:
		GLFWwindow* m_window;

		VertexArray* vao;
		VertexBuffer* vbo;
		ElementBuffer* ibo;

		GLuint shaderProgram = 0;
		GLuint vertexShader = 0;
		GLuint fragmentShader = 0;

	};
}

