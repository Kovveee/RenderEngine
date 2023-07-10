#include "Renderer.h"

namespace RenderEngine 
{
	Renderer::Renderer() : m_window(NULL)
	{
		if (!glfwInit())
			return;
		
		m_window = glfwCreateWindow(640, 700, "Hello World!", NULL, NULL);

		if (!m_window) {
			glfwTerminate();
			return;
		}	
	}
	Renderer::~Renderer()
	{
	}
	void Renderer::Render() 
	{
		glfwMakeContextCurrent(m_window);

		if (GLEW_OK != glewInit())
			return;


		while (!glfwWindowShouldClose(m_window)) 
		{
			glClearColor(0.2f, 0.4f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

		glfwTerminate();

		return;
	}

}