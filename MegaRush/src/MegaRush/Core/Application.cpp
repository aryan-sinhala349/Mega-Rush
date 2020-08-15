#include "Application.h"

#include <glad/glad.h>

namespace MegaRush
{
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	uint32_t indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	std::string vertexSource = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;
		
		void main()
		{
			gl_Position = vec4(aPos, 1.0);
		}
	)";

	std::string fragmentSource = R"(
		#version 330 core

		out vec4 color;

		void main()
		{
			color = vec4(0.2, 0.3, 0.8, 1.0);
		}
	)";

	uint32_t vao, vbo, ebo;
	uint32_t shaderProgram;

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
		
		glCreateBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		uint32_t vertexShader, fragmentShader;
		const char* vSourceCode = vertexSource.c_str();
		const char* fSourceCode = fragmentSource.c_str();
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		int success;
		char* infoLog = new char[512];
		glShaderSource(vertexShader, 1, &vSourceCode, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			MR_CORE_ERROR("Failed to compile vertex shader: {0}", infoLog);
		}

		glShaderSource(fragmentShader, 1, &fSourceCode, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			MR_CORE_ERROR("Failed to compile fragment shader: {0}", infoLog);
		}

		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			MR_CORE_ERROR("Failed to link shader program: {0}", infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

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
			
			glUseProgram(shaderProgram);
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint32_t), GL_UNSIGNED_INT, 0);

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