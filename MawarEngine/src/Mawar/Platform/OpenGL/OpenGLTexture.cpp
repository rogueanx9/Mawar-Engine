#include "mpch.hpp"
#include "OpenGLTexture.hpp"
#include "stb_image.h"

namespace Mawar
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, const void* data)
		: m_Width(width), m_Height(height)
	{
		M_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		m_Bpp = 4;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		SetData(data, m_Width * m_Height * m_Bpp);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		M_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		M_CORE_ASSERT(data, "Failed to load texture!");
		M_CORE_TRACE("Loaded texture: {0} ({1}x{2})", path, width, height);

		m_Width = width;
		m_Height = height;

		switch (channels)
		{
		case 3: m_InternalFormat = GL_RGB8; m_DataFormat = GL_RGB; m_Bpp = 3; break;
		case 4: m_InternalFormat = GL_RGBA8; m_DataFormat = GL_RGBA; m_Bpp = 4; break;
		default: M_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format is not supported!");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		M_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(const void* data, uint32_t size)
	{
		M_PROFILE_FUNCTION();

		M_CORE_ASSERT(size == m_Width * m_Height * m_Bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		M_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);
	}
}
