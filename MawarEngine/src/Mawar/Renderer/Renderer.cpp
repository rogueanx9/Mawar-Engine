#include "mpch.hpp"
#include "Renderer.hpp"

#include "Mawar/Platform/OpenGL/OpenGLShader.hpp"

namespace Mawar
{
    Renderer::SceneData Renderer::m_SceneData;
    ShaderLibrary* Renderer::s_ShaderLibrary = new ShaderLibrary;

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(const OrthographicCamera& camera)
    {
        m_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4f("u_ViewProjection", m_SceneData.ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4f("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::OnWindowResize(0, 0, width, height);
    }
}