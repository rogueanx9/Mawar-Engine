#pragma once

#include "Mawar/Core/Core.hpp"

namespace Mawar
{
	class M_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressed_impl(keycode); }

		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressed_impl(button); }
		static std::pair<float,float> GetMousePosition() { return s_Instance->GetMousePosition_impl(); }
		static float GetMouseX() { return s_Instance->GetMouseX_impl(); }
		static float GetMouseY() { return s_Instance->GetMouseY_impl(); }

	protected:
		virtual bool IsKeyPressed_impl(int keycode) = 0;

		virtual bool IsMouseButtonPressed_impl(int button) = 0;
		virtual std::pair<float, float> GetMousePosition_impl() = 0;
		virtual float GetMouseX_impl() = 0;
		virtual float GetMouseY_impl() = 0;

	private:
		static Input* s_Instance;
	};
}