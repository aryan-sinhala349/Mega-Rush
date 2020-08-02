#include "Application.h"

namespace MegaRush
{
	Application::Application() : m_Running(false)
	{
		MR_CORE_INFO("Created Application");

		m_Running = true;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			OnEvent(WindowCloseEvent());
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MR_BIND_EVENT_FN(OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		MR_CORE_INFO("WINDOW CLOSE EVENT");
		return false;
	}
}