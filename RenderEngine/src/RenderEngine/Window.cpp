#include "Window.h"

Window::Window(WindowData& props)
{ 
	Init(props); 
}
void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);

}
void Window::SetVSync(bool enable)
{
	if (enable)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}

void Window::Init(WindowData& props)
{
	int success = glfwInit();
	if (!success)
	{
		std::cout << "ERROR::GLFW::INIT" << std::_Get_asan_aligned_first_end;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), NULL, NULL);

	glfwMakeContextCurrent(m_window);

	SetVSync(true);

	glfwSetWindowUserPointer(m_window, &data);

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			WindowCloseEvent event;
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (data.EventCallback != NULL)
				data.EventCallback(event);
		});
	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			WindowResizeEvent event;
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			if (data.EventCallback != NULL)
				data.EventCallback(event);

		});
	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});
	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);

		});
	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, false);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, true);
				data.EventCallback(event);
				break;
			}
			}
		});

}