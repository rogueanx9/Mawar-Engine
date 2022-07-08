#pragma once

#include "Event.hpp"

namespace Mawar
{
	class M_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << 'x' << m_Height;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication);
		EVENT_CLASS_TYPE(WindowResize);

	private:
		unsigned int m_Width, m_Height;
	};

	class M_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryApplication);
		EVENT_CLASS_TYPE(WindowClose);
	};

	class M_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryApplication);
		EVENT_CLASS_TYPE(AppTick);
	};

	class M_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryApplication);
		EVENT_CLASS_TYPE(AppUpdate);
	};

	class M_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryApplication);
		EVENT_CLASS_TYPE(AppRender);
	};
}