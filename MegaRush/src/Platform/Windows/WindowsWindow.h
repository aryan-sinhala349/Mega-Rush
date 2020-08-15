#pragma once

#include "MegaRush/Core/Window.h"
#include "MegaRush/Renderer/GraphicsContext.h"

#include <Windows.h>

namespace MegaRush
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }
		virtual const char* GetTitle() const override { return m_Data.Title.c_str(); }
		virtual void* GetNativeWindow() override { return m_HWND; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		struct WindowData
		{
			uint32_t Width, Height;
			std::string Title;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		HWND m_HWND;
		WindowData m_Data;
		Scope<GraphicsContext> m_Context;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		static std::unordered_map<HWND, WindowsWindow*> s_Windows;
		static LRESULT WndProc(_In_ HWND   hwnd, _In_ UINT   uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
	};
}