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
		Shader* shaderProgram;
		glm::vec3 color = glm::vec3(0.f,0.f,0.f);
	};
}

