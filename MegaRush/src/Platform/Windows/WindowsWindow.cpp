#include "WindowsWindow.h"

#include "MegaRush/Core/Log.h"
#include "MegaRush/Events/ApplicationEvent.h"

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

		RegisterClass(&wndClass);

		m_HWND = CreateWindowEx(0, className.c_str(), className.c_str(), WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, CW_USEDEFAULT, props.Width, props.Height,
								NULL, NULL, hInstance, NULL);

		if (m_HWND == nullptr)
		{
			MR_CORE_ERROR("Window is null!");
			return;
		}

		s_Windows[m_HWND] = this;

		ShowWindow(m_HWND, SW_SHOW);
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
		SwapBuffers(GetDC(m_HWND));
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