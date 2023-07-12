#include "Renderer.h"

#include <iostream>


namespace RenderEngine
{
	Renderer::Renderer() 
		: m_window(NULL)
	{
		if (!glfwInit())
			return;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(640, 700, "Hello World!", NULL, NULL);

		if (!m_window) {
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);

		glfwSwapInterval(1);

		if (GLEW_OK != glewInit())
			return;
		Init();
	}

	Renderer::~Renderer()
	{
		
	}

	void Renderer::Init()
	{
		Vertex vertices[] =
		{
			{glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(1.0f, 0.f, 0.f),	glm::vec2(0,0)},
			{glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.f, 1.0f, 0.f),	glm::vec2(0,0)},
			{glm::vec3(0.0f, 0.5f, 0.0f),		glm::vec3(0.f, 0.f, 1.0f),	glm::vec2(0,0)}
		};

		const unsigned int indices[] =
		{
			0,1,2
		};
		
		vao = new VertexArray();
		vao->Bind();

		vbo = new VertexBuffer(3, vertices);
		vbo->Bind();

		ibo = new ElementBuffer(3, indices);
		ibo->Bind();

		vao->InitVertexArray();

		
		vao->Unbind();
		vbo->Unbind();
		ibo->Unbind();

		shaderProgram = new Shader("C:\\dev\\RenderEngine\\RenderEngine\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\vShader.vert", "C:\\dev\\RenderEngine\\RenderEngine\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\fShader.frag");
		shaderProgram->InitUniformVariable("colorChange");
	}


	void Renderer::Render() 
	{
		while (!glfwWindowShouldClose(m_window)) 
		{
			glClearColor(0.2f, 0.4f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shaderProgram->UseProgram();
			vao->Bind();
			shaderProgram->setUniform<glm::vec3>("colorChange", color);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
			vao->Unbind();

			color.x += 0.001f;
			color.y += 0.001f;
			color.z += 0.001f;
			if (color.x > 1.f) {
				color.x = 0.f;
			}
			if (color.y > 1.f) {
				color.y = 0.f;
			}
			if (color.z > 1.f) {
				color.z = 0.f;
			}

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

		glfwTerminate();

		return;
	}

}