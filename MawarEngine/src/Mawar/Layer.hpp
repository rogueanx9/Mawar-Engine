#pragma once

#include "Mawar/Events/Event.hpp"

namespace Mawar
{
	class M_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		std::string GetName() const { return m_Debugname; }

	protected:
		std::string m_Debugname;
	};
}