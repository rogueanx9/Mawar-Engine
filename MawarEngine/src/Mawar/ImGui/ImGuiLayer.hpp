#pragma once

#include "Mawar/Core.hpp"
#include "Mawar/Layer.hpp"

namespace Mawar
{
	class M_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	private:
		float m_Time = 0.0f;
	};
}