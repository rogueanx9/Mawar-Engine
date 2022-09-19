#pragma once

#include "Mawar/Core/Input.hpp"

namespace Mawar
{
	class M_API WindowsInput : public Input
	{
	protected:
		bool IsKeyPressed_impl(int keycode) override;

		bool IsMouseButtonPressed_impl(int button) override;
		std::pair<float, float> GetMousePosition_impl() override;
		float GetMouseX_impl() override;
		float GetMouseY_impl() override;
	};
}