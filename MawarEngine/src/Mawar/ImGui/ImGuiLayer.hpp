#pragma once

#include "Mawar/Core/Core.hpp"
#include "Mawar/Core/Layer.hpp"

#include "Mawar/Events/ApplicationEvent.hpp"
#include "Mawar/Events/KeyEvent.hpp"
#include "Mawar/Events/MouseEvent.hpp"

namespace Mawar
{
	class M_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void Begin();
		void End();

	private:
		bool m_show_demo_window = true;
		bool m_show_another_window = false;
		float m_Time = 0.0f;
	};
}