#pragma once

#include "Mawar/Renderer/Texture.hpp"

#include <glad/glad.h>

namespace Mawar
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height, const void* data);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		void SetData(const void* data, uint32_t size) override;

		void Bind(uint32_t slot = 0) const override;

		bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}

	private:
		uint32_t m_RendererID;
		std::string m_Path;

		uint32_t m_Width;
		uint32_t m_Height;

		GLenum m_InternalFormat = 0, m_DataFormat = 0;
		uint8_t m_Bpp;
	};
}