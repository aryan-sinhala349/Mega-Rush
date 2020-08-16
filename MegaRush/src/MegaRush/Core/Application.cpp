#include "Application.h"

#include <glad/glad.h>

namespace MegaRush
{
	glm::vec3 vertices[] =
	{
		{0.0f, 0.0f, 0.0f}
	};

	uint32_t vao, vbo;

	Application* Application::s_Instance = nullptr;

	Application::Application(const char* title) : m_Running(false)
	{
		MR_CORE_ASSERT(!s_Instance, "Application already created!");

		m_Window = Window::Create(WindowProps(m_Width, m_Height, title));
		m_Window->SetEventCallback(MR_BIND_EVENT_FN(OnEvent));

		m_RendererAPI = RendererAPI::Create();
		m_RendererAPI->Init();

		m_RendererAPI->SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);

		m_Shader = Shader::Create("assets\\shaders\\Default.glsl");

		s_Instance = this;

		m_Running = true;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_RendererAPI->Clear();
			
			m_Shader->Bind();
			glDrawArrays(GL_POINTS, 0, sizeof(vertices) / sizeof(glm::vec3));

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(MR_BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(MR_BIND_EVENT_FN(OnWindowClose));
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_RendererAPI->SetViewport(0, 0, e.GetWidth(), e.GetHeight());
		MR_CORE_WARN("Resized window: {0} x {1}", e.GetWidth(), e.GetHeight());
		return false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		MR_CORE_INFO("Closed window {0}", m_Window->GetTitle());
		return false;
	}
}