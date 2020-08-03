#pragma once

#include <string>
#include <functional>

#include "MegaRush\Events\Event.h"

namespace MegaRush
{
	struct WindowProps
	{
		uint32_t Width, Height;
		std::string Title;

		WindowProps(uint32_t width = 1280, uint32_t height = 720, std::string title = "MegaRush Window") : Width(width), Height(height), Title(title)
		{ }
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual void* GetNativeWindow() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual const char* GetTitle() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}
