#include "WindowInput.h"


bool WindowInput::IsKeyPressed(const KeyCode key)
{
	auto* window = RenderEngine::Application::GetInstance().GetWindow().GetNativeWindow();
	auto state = glfwGetKey(window, key);
	return state == GLFW_PRESS;
}
bool WindowInput::IsMouseButtonPressed(MouseCode button)
{
	auto* window = RenderEngine::Application::GetInstance().GetWindow().GetNativeWindow();
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}
glm::vec2 WindowInput::GetMousePosition()
{
	auto* window = RenderEngine::Application::GetInstance().GetWindow().GetNativeWindow();
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	return { (float)mouseX, (float)mouseY };
}
float WindowInput::GetMouseX()
{
	return GetMousePosition().x;
}
float WindowInput::GetMouseY()
{
	return GetMousePosition().y;
}
