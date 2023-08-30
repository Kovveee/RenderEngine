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
		m_models.push_back(new Model("cube1", "src\\Models\\cube\\untitled2.obj"));
		m_models.push_back(new Model("cube2", "src\\Models\\cube\\untitled2.obj"));
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

			if (WindowInput::IsKeyPressed(KeyCodes::KEY_W))
			{
				*m_models[0]->GetTranslation() = *m_models[0]->GetTranslation() + glm::vec3(0, 0, 1);
			}
			if (WindowInput::IsKeyPressed(KeyCodes::KEY_S))
			{
				*m_models[0]->GetTranslation() = *m_models[0]->GetTranslation() + glm::vec3(0, 0, -1);
			}
			if (WindowInput::IsKeyPressed(KeyCodes::KEY_A))
			{
				*m_models[0]->GetTranslation() = *m_models[0]->GetTranslation() + glm::vec3(1, 0, 0);
			}
			if (WindowInput::IsKeyPressed(KeyCodes::KEY_D))
			{
				*m_models[0]->GetTranslation() = *m_models[0]->GetTranslation() + glm::vec3(-1, 0, 0);
			}
			

			glm::vec2 mousePos =glm::vec2(WindowInput::GetMouseX() - m_window->GetWidth() / 2, (WindowInput::GetMouseY() - m_window->GetHeight() / 2));
			mousePos.y = -mousePos.y;
			float rotationDot = glm::dot(mousePos, mechFront) / (glm::length(mousePos) * glm::length(mechFront));
			float acossValue = rotationDot;
			float rotationAngle = glm::acos(acossValue);
			if (mousePos.x > 0)
				rotationAngle = -rotationAngle;
			
			std::cout << glm::degrees(rotationAngle) << " " << mousePos.x <<" " << mousePos.y << std::endl;

			*m_models[0]->GetRotation() = glm::vec3(0, glm::degrees(rotationAngle), 0);

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

