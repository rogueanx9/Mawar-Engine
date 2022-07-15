#pragma once

#include "mpch.hpp"
#include "Mawar/Core.hpp"

namespace Mawar
{
	// Current event system is blocking. Meaning that it should be dispatched
	// after listening.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication      = BIT(0),
		EventCategoryInput            = BIT(1),
		EventCategoryKeyboard         = BIT(2),
		EventCategoryMouse            = BIT(3),
		EventCategoryMouseButton      = BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticEventType() { return EventType::##type; }\
                               EventType GetEventType() const override { return getStaticEventType(); }\
                               const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags() const override { return category; }

	class Event // Interface
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

	private:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& e) : m_Event(e) {}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::getStaticEventType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}