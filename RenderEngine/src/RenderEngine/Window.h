#pragma once
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <functional>
#include "Event/WindowEvents.h"
#include "Event/InputEvents.h"

using EventCallbackFn = std::function<void(Event&)>;

struct WindowData
{
	std::string title;
	unsigned int width, height;
	EventCallbackFn EventCallback;
};

class Window
{
public:
	Window(WindowData& props);
	Window* Create(WindowData& props){ return new Window(props); }
	void Init(WindowData& props);
	void Update();
	void SetVSync(bool enable);
	void SetEventCallback(const EventCallbackFn& callback) { data.EventCallback = callback; }
	int GetWidth() { return data.width; }
	int GetHeight() { return data.height; }
	std::string GetTitle() { return data.title; }
	GLFWwindow* GetNativeWindow() { return m_window; }
private:
	GLFWwindow* m_window;
	WindowData data;
};

