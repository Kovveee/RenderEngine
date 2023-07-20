#pragma once

#include "Core.h"
#include "Renderer/Renderer.h"

namespace RenderEngine {
	class RENDERENGINE_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		Renderer* m_renderer = NULL;
		

	};

	Application* CreateApplication();
}