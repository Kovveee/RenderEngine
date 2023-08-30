#pragma once
#pragma once

#include "Renderer/KeyCodes.h"
#include "Renderer/MouseCodes.h"

#include "glm/glm.hpp"

#include "Application.h"

class WindowInput
{
public:
	static bool IsKeyPressed(KeyCode key);

	static bool IsMouseButtonPressed(MouseCode button);

	static glm::vec2 GetMousePosition();

	static float GetMouseX();

	static float GetMouseY();
};