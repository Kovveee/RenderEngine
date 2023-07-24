#include "Application.h"

namespace RenderEngine {
	Application::Application()
	{
		// Init openGL
		if (!glfwInit())
			return;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



		window = glfwCreateWindow(1920, 1080, "Main Window", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window);

		glfwSwapInterval(1);

		glewExperimental = GL_TRUE;

		if (GLEW_OK != glewInit())
			return;

		m_renderer = new Renderer(window, 1920, 1080);
	}

	Application::~Application()
	{
		delete m_renderer;
	}

	void Application::Run() {
		//m_renderer->AddModel("cube", "src\\Models\\cube\\untitled.obj");
		m_renderer->Render();
	}
}

