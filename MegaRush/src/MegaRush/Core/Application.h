#pragma once

#include "Log.h"
#include "Window.h"

#include "MegaRush/Renderer/RendererAPI.h"

#include "MegaRush/Events/ApplicationEvent.h"

int main(int argc, char** argv);

namespace MegaRush
{
	class Application
	{
	public:
		Application(const char* title = "MegaRush Window");
		virtual ~Application();

		void OnEvent(Event& e);

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }

	private:
		bool m_Running;
		uint32_t m_Width = 1280, m_Height = 720;
		Scope<Window> m_Window;
		Scope<RendererAPI> m_RendererAPI;

		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		friend int ::main(int argc, char** argv);

		static Application* s_Instance;
	};

	Application* CreateApplication();
}