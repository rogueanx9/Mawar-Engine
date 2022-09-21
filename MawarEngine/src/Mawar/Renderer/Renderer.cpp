#include "mpch.hpp"
#include "Renderer.hpp"

#include "Mawar/Renderer/Renderer2D.hpp"
#include "Mawar/Platform/OpenGL/OpenGLShader.hpp"

namespace Mawar
{
    Renderer::SceneData Renderer::m_SceneData;
    Ref<ShaderLibrary> Renderer::s_ShaderLibrary = CreateRef<ShaderLibrary>();

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
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