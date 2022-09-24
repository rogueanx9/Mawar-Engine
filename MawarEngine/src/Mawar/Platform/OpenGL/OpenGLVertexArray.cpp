#include "mpch.hpp"
#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>

namespace Mawar
{
	static GLenum ToOpenGLType(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::None:          return GL_FALSE;
		case ShaderDataType::Float:         return GL_FLOAT;
		case ShaderDataType::Float2:        return GL_FLOAT;
		case ShaderDataType::Float3:        return GL_FLOAT;
		case ShaderDataType::Float4:        return GL_FLOAT;
		case ShaderDataType::Int:           return GL_INT;
		case ShaderDataType::Int2:          return GL_INT;
		case ShaderDataType::Int3:          return GL_INT;
		case ShaderDataType::Int4:          return GL_INT;
		case ShaderDataType::Mat3:          return GL_FLOAT;
		case ShaderDataType::Mat4:          return GL_FLOAT;
		case ShaderDataType::Bool:          return GL_BOOL;
		}

		M_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return GL_FALSE;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		M_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		M_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		M_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unind() const
	{
		M_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		M_PROFILE_FUNCTION();

		M_CORE_ASSERT(vertexBuffer->GetLayout().GetElement().size(), "VertexBuffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex, 
				                  element.Count(), 
				                  ToOpenGLType(element.type),
				                  element.normalize ? GL_TRUE : GL_FALSE,
				                  layout.GetStride(), 
				                  (const void*)element.offset);
			m_VertexBufferIndex++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> indexBuffer)
	{
		M_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}