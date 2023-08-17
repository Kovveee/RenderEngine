#pragma once

#include <memory>

#include "Core.h"
#include "Renderer/Renderer.h"
#include "Window.h"

#include "Event/WindowEvents.h"
#include "Event/InputEvents.h"


namespace RenderEngine {
	class RENDERENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		GLFWwindow* m_Window;
		void OnEvent(Event& e);
		bool WindowClose(WindowCloseEvent& e);
		bool WindowResize(WindowResizeEvent& e);
		void Run();
	private:
		Renderer* m_renderer = NULL;
		Window* m_window;
		bool m_isRunning;
};

	Application* CreateApplication();
}