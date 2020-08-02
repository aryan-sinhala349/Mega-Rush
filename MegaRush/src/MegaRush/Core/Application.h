#pragma once

#include "Log.h"

#include "MegaRush/Events/ApplicationEvent.h"

int main(int argc, char** argv);

namespace MegaRush
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

	private:
		bool m_Running;

		void Run();

		bool OnWindowClose(WindowCloseEvent& e);

		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}