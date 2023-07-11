#include "Renderer.h"

#include <iostream>

namespace RenderEngine
{
	Renderer::Renderer() : m_window(NULL)
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
		



		std::string vertex_shader =
			"#version 330 core\n" 
			"\n"
			"layout(location = 0) in vec3 Position;\n" 
			"layout(location = 1) in vec3 Color;\n" 
			"void main(){\n" 
			"gl_Position = vec4(Position,1.0);\n"
			"}\n";

		const char* vertexsrc = vertex_shader.c_str();

		std::string fragment_shader =
			"#version 330 core\n"
			"\n"
			"out vec4 color;"
			"\n"
			"void main()\n"
			"{\n"
			"color = vec4(1.0,0.0,0.0,1.0);\n"
			"}\n";

		const char* fragmentsrc = fragment_shader.c_str();

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexsrc, NULL);
		glCompileShader(vertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1,&fragmentsrc, NULL);
		glCompileShader(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}


	void Renderer::Render() 
	{
		while (!glfwWindowShouldClose(m_window)) 
		{
			glClearColor(0.2f, 0.4f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shaderProgram);
			vao->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
			vao->Unbind();

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

		glfwTerminate();

		return;
	}

}