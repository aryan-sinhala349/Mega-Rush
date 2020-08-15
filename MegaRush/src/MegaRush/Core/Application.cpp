#include "Application.h"

namespace MegaRush
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const char* title) : m_Running(false)
	{
		MR_CORE_ASSERT(!s_Instance, "Application already created!");

		m_Window = Window::Create(WindowProps(m_Width, m_Height, title));
		m_Window->SetEventCallback(MR_BIND_EVENT_FN(OnEvent));

		m_RendererAPI = RendererAPI::Create();
		m_RendererAPI->Init();

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