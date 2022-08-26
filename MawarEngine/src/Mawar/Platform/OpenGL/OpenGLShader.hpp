#pragma once

#include "Mawar/Renderer/Shader.hpp"
#include <glm/glm.hpp>

namespace Mawar
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformInt(const std::string& name, int vector);

		void UploadUniformFloat(const std::string& name, float vector);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);

		void UploadUniformMat3f(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4f(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};
}