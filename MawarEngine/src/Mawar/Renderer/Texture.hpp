#pragma once

#include "Mawar/Core/Core.hpp"
#include <string>

namespace Mawar
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		//virtual void Unbind(uint32_t slot = 0) const = 0; // TODO
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height, const void* data = 0);
		static Ref<Texture2D> Create(const std::string& path);
	};
}