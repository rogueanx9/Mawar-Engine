#include "mpch.hpp"
#include "Shader.hpp"

#include "Mawar/Renderer/Renderer.hpp"

#include "Mawar/Platform/OpenGL/OpenGLShader.hpp"

namespace Mawar
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: M_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		M_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: M_CORE_ASSERT(false, "RendererAPI::None is not supported."); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		M_CORE_ASSERT(false, "Unknown Renderer API.");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		M_CORE_ASSERT(!Exist(name), "You cannot create same shader twice.");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		Add(shader->GetName(), shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		M_CORE_ASSERT(Exist(name), "Shader not found.");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exist(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}
