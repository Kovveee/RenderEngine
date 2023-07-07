#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace RenderEngine 
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Render();

	private:
		GLFWwindow* m_window;

	};
}

