#include "mpch.hpp"
#include "Renderer.hpp"

namespace Mawar
{
    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}