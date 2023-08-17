#pragma once
#include <vector>
#include <iostream>
#include <functional>


enum EventType {
	None = 0,
	WindowResize,WindowClose,WindowMinimize,
	KeyPressed, KeyReleased,
	MouseMoved,MouseButtonPressed, MouseButtonReleased, MouseScrolled
};


class Event
{
	friend class EventDispather;
public:
	bool m_handled = false;
	bool IsHandled() { return m_handled; }
	virtual const char* GetName() const = 0;
	virtual EventType GetType() const = 0;

#define SET_FUNCTIONS(type) static EventType GetStaticType() {return EventType::type; }\
							virtual EventType GetType()  const override {return GetStaticType(); }\
							virtual const char* GetName()  const override {return #type; }
};
class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	EventDispatcher(Event& event)
		: m_event(event){}

	template<typename T>
	bool Dispatch(EventFn<T> func)
	{
		if(m_event.GetType() == T::GetStaticType())
		{ 
			m_event.m_handled |= func(*(T*)&m_event);
			return true;
		}
		return false;
	}
private:
	Event& m_event;
};