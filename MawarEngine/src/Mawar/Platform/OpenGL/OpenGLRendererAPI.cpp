#include "mpch.hpp"
#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Mawar
{
	void OpenGLRendererAPI::Init()
	{
		M_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		M_PROFILE_FUNCTION();

		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		M_PROFILE_FUNCTION();

		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		M_PROFILE_FUNCTION();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count)
	{
		M_PROFILE_FUNCTION();

		uint32_t indexCount = count == 0 ? vertexArray->GetIndexBuffer()->GetCount() : count;
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	}

}