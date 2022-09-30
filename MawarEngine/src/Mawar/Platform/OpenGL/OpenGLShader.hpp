#pragma once

#include "Mawar/Renderer/Shader.hpp"
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Mawar
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, std::string_view vertexSource, std::string_view fragmentSource);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;
		std::string GetName() const override { return m_Name; }

		void SetInt(const std::string& name, int value) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		void UploadUniformInt(const std::string& name, int vector);

		void UploadUniformFloat(const std::string& name, float vector);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);

		void UploadUniformMat3f(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}