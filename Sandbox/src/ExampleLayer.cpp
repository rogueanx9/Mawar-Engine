#include "mpch.hpp"
#include "ExampleLayer.hpp"

LayerExample::LayerExample()
	: Layer("Example"), m_CameraController(4 / 3), m_TransformPosition(0.0f)
{
	/// <summary>
	/// OpenGL Rendering Object
	/// </summary>
	m_VertexArray = Mawar::VertexArray::Create();
	m_SquareVertexArray = Mawar::VertexArray::Create();

	/// <summary>
	/// Triangle
	/// </summary>
	float vertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	Mawar::Ref<Mawar::VertexBuffer> triangleVB;
	triangleVB = Mawar::VertexBuffer::Create(vertices, sizeof(vertices));
	triangleVB->SetLayout({
		{Mawar::ShaderDataType::Float3, "a_Position"},
		{Mawar::ShaderDataType::Float2, "a_TexCoord"}
		});
	m_VertexArray->AddVertexBuffer(triangleVB);

	unsigned int indices[6] = { 0,1,2,2,3,0 };
	Mawar::Ref<Mawar::IndexBuffer> triangleIB;
	triangleIB = Mawar::IndexBuffer::Create(indices, 6);
	m_VertexArray->SetIndexBuffer(triangleIB);

	/// <summary>
	/// Square
	/// </summary>
	float squareVertices[5 * 4] =
	{
		-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
		 0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
		 0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
		-0.75f,  0.75f, 0.0f, 0.0f, 1.0f
	};
	Mawar::Ref<Mawar::VertexBuffer> squareVB;
	squareVB = Mawar::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{Mawar::ShaderDataType::Float3, "a_Position"},
		{Mawar::ShaderDataType::Float2, "a_TexCoord"}
		});
	m_SquareVertexArray->AddVertexBuffer(squareVB);

	unsigned int squareIndices[] = { 0,1,2,2,3,0 };
	Mawar::Ref<Mawar::IndexBuffer> squareIB;
	squareIB = Mawar::IndexBuffer::Create(squareIndices, 6);
	m_SquareVertexArray->SetIndexBuffer(squareIB);

	auto m_Shader = Mawar::Renderer::GetShaderLibrary()->Load("assets/shaders/Texture.glsl");

	std::string SquarevertexSource = R"(
             #version 330 core

             layout(location=0) in vec3 a_Position;
             layout(location=1) in vec2 a_TexCoord;

             uniform mat4 u_ViewProjection;
             uniform mat4 u_Transform;

             out vec3 v_Position;
             out vec2 v_TexCoord;

             void main()
             {
                  v_Position = a_Position;
                  v_TexCoord = a_TexCoord;
                  gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
             }
        )";

	std::string SquarefragmentSource = R"(
             #version 330 core

             layout(location=0) out vec4 color;

             in vec3 v_Position;
             in vec2 v_TexCoord;

             uniform vec4 u_Color;

             void main()
             {
                  color = u_Color;
             }
        )";

	Mawar::Renderer::GetShaderLibrary()->Add(Mawar::Shader::Create("SquareShader", SquarevertexSource, SquarefragmentSource));

	m_Texture = Mawar::Texture2D::Create("assets/images/bird.png");
	m_CatTexture = Mawar::Texture2D::Create("assets/images/cat.png");
	m_Shader->Bind();
	m_Shader->SetInt("u_Texture", 0); // Upload slot ID

	m_CameraController.SetRotation(true);
}

void LayerExample::OnUpdate(Mawar::Timestep ts)
{
	//M_TRACE("Delta time: {0}s {1}ms", ts.GetSecond(), ts.GetMiliSecond());
	m_CameraController.OnUpdate(ts);

	Mawar::RenderCommand::SetClearColor({ ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w });
	Mawar::RenderCommand::Clear();

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	Mawar::Renderer::BeginScene(m_CameraController.GetCamera());

	auto m_SquareShader = Mawar::Renderer::GetShaderLibrary()->Get("SquareShader");
	m_SquareShader->Bind();
	glm::vec4 square_color(SquareColor.x, SquareColor.y, SquareColor.z, SquareColor.w);
	m_SquareShader->SetFloat4("u_Color", square_color);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			glm::vec3 pos(0.18f * j, 0.18f * i, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Mawar::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transform);
		}
	}

	auto m_Shader = Mawar::Renderer::GetShaderLibrary()->Get("Texture");

	glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), m_TransformPosition);
	glm::mat4 moveSlight = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.0f));
	m_Texture->Bind();
	Mawar::Renderer::Submit(m_Shader, m_VertexArray, transform1);
	m_CatTexture->Bind();
	Mawar::Renderer::Submit(m_Shader, m_VertexArray, transform1 + moveSlight);
	Mawar::Renderer::EndScene();
}
void LayerExample::OnImGuiRender()
{
	ImGui::Begin("Hello World!");
	ImGui::TextColored(TextCol, "Halo ini window baru dari layer example\npada aplikasi sandbox.");
	ImGui::ColorEdit3("Text Color", (float*)&TextCol);
	ImGui::ColorEdit3("Clear Color", (float*)&ClearColor);
	ImGui::ColorEdit3("Square Color", (float*)&SquareColor);
	ImGui::End();
}
void LayerExample::OnEvent(Mawar::Event& e)
{
	m_CameraController.OnEvent(e);
}