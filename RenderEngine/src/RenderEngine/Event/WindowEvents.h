#pragma once
#include "Event.h"


class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;
	SET_FUNCTIONS(WindowClose);
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent() = default;
	SET_FUNCTIONS(WindowResize);
};
class WindowMinimizeEvent: public Event
{
public:
	WindowMinimizeEvent() = default;
	SET_FUNCTIONS(WindowResize);
};
