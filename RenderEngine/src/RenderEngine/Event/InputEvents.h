#pragma once
#include "Event.h"
#include "../Renderer/MouseCodes.h"
#include "../Renderer/KeyCodes.h"


class MouseButtonPressedEvent : public Event
{
public:
	MouseButtonPressedEvent(MouseCode code)
		: m_code(code){}

	MouseCode GetMouseButton() const { return m_code; }

	SET_FUNCTIONS(MouseButtonPressed);
protected:
	MouseCode m_code;
};
class MouseButtonReleasedEvent : public Event
{
public:
	MouseButtonReleasedEvent(MouseCode code)
		: m_code(code){}

	SET_FUNCTIONS(MouseButtonReleased);

	MouseCode GetMouseButton() const { return m_code; }

protected:
	MouseCode m_code;
};
class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(const float mouseX, const float mouseY)
		:m_mouseX(mouseX), m_mouseY(mouseY) {}

	float GetMouseX() const { return m_mouseX; }
	float GetMouseY() const { return m_mouseY; }
	SET_FUNCTIONS(MouseMoved);
private:
	float m_mouseX, m_mouseY;
};
class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(const float offsetX, const float offsetY)
		:m_offsetX(offsetX), m_offsetY(offsetY){}

	float GetOffsetX() const { return m_offsetX; }
	float GetOffsetY() const { return m_offsetY; }
	
	SET_FUNCTIONS(MouseScrolled);
private:
	float m_offsetX, m_offsetY;
};

class KeyPressedEvent: public Event
{
public:
	KeyPressedEvent(KeyCode code, bool isRepeat)
		: m_code(code), m_isRepeat(isRepeat){}
	KeyCode GetKey() { return m_code; }
	SET_FUNCTIONS(KeyPressed);
protected:
	KeyCode m_code;
	bool m_isRepeat;
};
class KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(KeyCode code)
		: m_code(code) {}
	SET_FUNCTIONS(KeyReleased);
	KeyCode GetKey() { return m_code; }
protected:
	KeyCode m_code;
};