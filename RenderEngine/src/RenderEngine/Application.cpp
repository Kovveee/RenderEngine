#include "Application.h"

namespace RenderEngine {
	Application::Application()
	{
		m_renderer = new Renderer();
	}

	Application::~Application()
	{
		delete m_renderer;
	}

	void Application::Run() {
		m_renderer->Render();
	}
}

