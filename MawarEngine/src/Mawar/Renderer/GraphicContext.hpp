#pragma once

namespace Mawar
{
	class GraphicContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}