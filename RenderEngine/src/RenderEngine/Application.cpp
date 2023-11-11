#include "Application.h"


#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace RenderEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		WindowData data = {"Main window",800,600};
		m_window = new Window(data);

		glewExperimental = GL_TRUE;

		if (GLEW_OK != glewInit())
			return;
		m_renderer = new Renderer(m_window->GetNativeWindow(), m_window->GetWidth(), m_window->GetHeight(), m_models);
		m_isRunning = true;

		s_Instance = this;

		m_models.push_back(new Model("mech", "src\\Models\\mech\\mech.obj"));

		m_window->SetEventCallback(BIND_EVENT(OnEvent));
	}

	Application::~Application()
	{
		delete m_renderer;
		delete m_window;
	}

	void Application::Run() {

		while(m_isRunning)
		{
			m_window->Update();
			m_renderer->Render();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(WindowClose));
		if(e.GetType() == EventType::KeyPressed)
		{
			KeyPressedEvent& event = (KeyPressedEvent&)e;
			
		}
		
	}
	bool Application::WindowClose(WindowCloseEvent& e)
	{
		m_isRunning = false;
		return true;
	}
}

