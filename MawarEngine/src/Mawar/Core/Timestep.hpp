#pragma once

namespace Mawar
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : m_Time(time) {}

		operator float() const { return m_Time; } // Default timestep is second

		const float GetSecond() const { return m_Time; }
		const float GetMiliSecond() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}