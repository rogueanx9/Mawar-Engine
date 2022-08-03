#include "mpch.hpp"
#include "Application.hpp"

#include "Mawar/Events/KeyEvent.hpp"
#include "Mawar/Events/MouseEvent.hpp"
#include "Mawar/Log.hpp"
#include "Mawar/Input.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Mawar
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	// Hackkkk
	static GLenum ToOpenGLType(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::None:          return GL_FALSE;
		case ShaderDataType::Float:         return GL_FLOAT;
		case ShaderDataType::Float2:        return GL_FLOAT;
		case ShaderDataType::Float3:        return GL_FLOAT;
		case ShaderDataType::Float4:        return GL_FLOAT;
		case ShaderDataType::Int:           return GL_INT;
		case ShaderDataType::Int2:          return GL_INT;
		case ShaderDataType::Int3:          return GL_INT;
		case ShaderDataType::Int4:          return GL_INT;
		case ShaderDataType::Mat3:          return GL_FLOAT;
		case ShaderDataType::Mat4:          return GL_FLOAT;
		case ShaderDataType::Bool:          return GL_BOOL;
		}

		M_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return GL_FALSE;
	}

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		M_CORE_ASSERT(!s_Instance, "Application already running.");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
			};
			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.Count(), ToOpenGLType(element.type), 
				                  element.normalize ? GL_TRUE : GL_FALSE, 
				                  layout.GetStride(), (const void*)element.offset);
			index++;
		}

		unsigned int indices[3] =
		{
			0, 1, 2
		};
		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

		std::string vertexSource = R"(
             #version 330 core

             layout(location=0) in vec3 a_Position;
             layout(location=1) in vec4 a_Color;

             out vec3 v_Position;
             out vec4 v_Color;

             void main()
             {
                  v_Position = a_Position;
                  v_Color = a_Color;
                  gl_Position = vec4(a_Position, 1.0);
             }
        )";

		std::string fragmentSource = R"(
             #version 330 core

             layout(location=0) out vec4 color;

             in vec3 v_Position;
             in vec4 v_Color;

             void main()
             {
                  color = vec4(v_Position * 0.5 + 0.6, 1.0);
                  color = v_Color;
             }
        )";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));
	}

	Application::~Application() {}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher{ e };
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			IMGUIClearColor clear_color = m_ImGuiLayer->GetClearColor();
			glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			//M_CORE_TRACE("Mouse Position: {0}, {1}", Input::GetMouseX(), Input::GetMouseY());

			// Main Window Update
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent&)
	{
		m_Running = false;
		return true;
	}
}