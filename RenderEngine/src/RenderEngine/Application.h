#pragma once

#include <memory>

#include "Core.h"
#include "Renderer/Renderer.h"
#include "Window.h"

#include "Event/WindowEvents.h"
#include "Event/InputEvents.h"

#include "Renderer/MouseCodes.h";
#include "Renderer/KeyCodes.h"

#include "WindowInput.h"

#include "Renderer/Model.h"


namespace RenderEngine {
	class RENDERENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		GLFWwindow* m_Window;
		void OnEvent(Event& e);
		bool WindowClose(WindowCloseEvent& e);
		void Run();

		static Application& GetInstance() { return *s_Instance; }
		Window& GetWindow() { return *m_window; }

	private:
		Renderer* m_renderer = NULL;
		Window* m_window;
		bool m_isRunning;
		static Application* s_Instance;
		std::vector<Model*> m_models;

		float mechRotation = 0;
		glm::vec2 mechFront = glm::vec2(0, 1);
};

	Application* CreateApplication();
}