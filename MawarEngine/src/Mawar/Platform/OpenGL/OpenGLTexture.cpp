#include "mpch.hpp"
#include "OpenGLTexture.hpp"
#include "stb_image.h"

#include <glad/glad.h>

namespace Mawar
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		M_CORE_ASSERT(data, "Failed to load texture!");
		M_CORE_TRACE("Loaded texture: {0} ({1}x{2})", path, width, height);
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		switch (channels)
		{
		case 3: internalFormat = GL_RGB8; dataFormat = GL_RGB; break;
		case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
		default: M_CORE_ASSERT(internalFormat & dataFormat, "Format is not supported!");
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}
