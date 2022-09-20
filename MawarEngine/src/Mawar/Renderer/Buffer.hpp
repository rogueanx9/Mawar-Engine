#pragma once

#include <cstdint>

namespace Mawar
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static std::pair<uint32_t, uint32_t> _GetBaseSizeAndCount(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::None:          return { 0,0 };
		case ShaderDataType::Float:         return { 4,1 };
		case ShaderDataType::Float2:        return { 4,2 };
		case ShaderDataType::Float3:        return { 4,3 };
		case ShaderDataType::Float4:        return { 4,4 };
		case ShaderDataType::Int:           return { 4,1 };
		case ShaderDataType::Int2:          return { 4,2 };
		case ShaderDataType::Int3:          return { 4,3 };
		case ShaderDataType::Int4:          return { 4,4 };
		case ShaderDataType::Mat3:          return { 4,3 * 3 };
		case ShaderDataType::Mat4:          return { 4,4 * 4 };
		case ShaderDataType::Bool:          return { 1,1 };
		}

		M_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return { 0,0 };
	}

	static uint32_t GetSizeOf(const ShaderDataType& type)
	{
		auto [baseSize, count] = _GetBaseSizeAndCount(type);
		return baseSize * count;
	}

	struct BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalize;

		BufferElement(const ShaderDataType& Type, const std::string& Name)
			: name(Name), type(Type), size(GetSizeOf(Type)), offset(0), normalize(false) {}

		uint32_t Count() const
		{
			auto [baseSize, count] = _GetBaseSizeAndCount(type);
			return count;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		inline const std::vector<BufferElement>& GetElement() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

}