#pragma once

#include "Core.h"


namespace RenderEngine {
	class RENDERENGINE_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Run();

	};
}