#include "Window.h"

#include "Log.h"

#ifdef MR_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace MegaRush
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef MR_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
		#endif

		MR_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
	}
}