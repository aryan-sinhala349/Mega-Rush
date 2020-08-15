#include "WindowsWindow.h"

#include "MegaRush/Core/Log.h"
#include "MegaRush/Events/ApplicationEvent.h"

#include "MegaRush/Renderer/RendererAPI.h"

#include <Windows.h>

namespace MegaRush
{
	std::unordered_map<HWND, WindowsWindow*> WindowsWindow::s_Windows = std::unordered_map<HWND, WindowsWindow*>();

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		HINSTANCE hInstance = GetModuleHandle(NULL);

		std::wstring className = std::wstring(props.Title.begin(), props.Title.end());
		
		WNDCLASS wndClass = {};

		wndClass.lpfnWndProc = WindowsWindow::WndProc;
		wndClass.hInstance = hInstance;
		wndClass.lpszClassName = className.c_str();

		RECT windowRect;
		windowRect.left = windowRect.top = 0;
		windowRect.right = props.Width;
		windowRect.bottom = props.Height;
		AdjustWindowRect(&windowRect, NULL, FALSE);
		MR_CORE_INFO("{0}", WindowResizeEvent(windowRect.right, windowRect.bottom).ToString());

		RegisterClass(&wndClass);

		m_HWND = CreateWindow(className.c_str(), className.c_str(), WS_OVERLAPPEDWINDOW, 
								CW_USEDEFAULT, CW_USEDEFAULT, windowRect.right, windowRect.bottom,
								NULL, NULL, hInstance, NULL);

		MR_CORE_ASSERT(m_HWND, "Window handle is null!");

		s_Windows[m_HWND] = this;

		ShowWindow(m_HWND, SW_SHOW);

		m_Context = GraphicsContext::Create(m_HWND);
		m_Context->Init();
	}

	void WindowsWindow::Shutdown()
	{
		if (m_HWND)
			DestroyWindow(m_HWND);
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg = {};
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	LRESULT WindowsWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* thisWindow = s_Windows[hwnd];

		switch (uMsg)
		{
			case WM_DESTROY:
				switch (RendererAPI::GetAPI())
				{
					case RendererAPI::API::None:
						break;

					case RendererAPI::API::OpenGL:
						auto context = wglGetCurrentContext();
						wglMakeCurrent(NULL, NULL);
						wglDeleteContext(context);
						ReleaseDC(hwnd, GetDC(hwnd));
						break;
				}
				return 0;

			case WM_CLOSE:
				thisWindow->m_Data.EventCallback(WindowCloseEvent());
				DestroyWindow(hwnd);
				return 0;

			case WM_SIZING:
				RECT clientRect;
				GetClientRect(hwnd, &clientRect);
				thisWindow->m_Data.Width = clientRect.right;
				thisWindow->m_Data.Height = clientRect.bottom;
				thisWindow->m_Data.EventCallback(WindowResizeEvent(clientRect.right, clientRect.bottom));
				return 0;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}