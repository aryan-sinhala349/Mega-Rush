#include "OpenGLContext.h"

#include "MegaRush/Core/Log.h"
#include <glad/glad.h>

#ifdef MR_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace MegaRush
{
	OpenGLContext::OpenGLContext(void* window) : m_WindowHandle(window)
	{

	}

	void OpenGLContext::Init()
	{
#ifdef MR_PLATFORM_WINDOWS
		HDC dc = GetDC((HWND)m_WindowHandle);

		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			16,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0,
		};

		auto pixelFormat = ChoosePixelFormat(dc, &pfd);
		MR_CORE_ASSERT(SetPixelFormat(dc, pixelFormat, &pfd), "Failed to create Pixel Format: {0}", GetLastError());

		HGLRC context = wglCreateContext(dc);
		MR_CORE_ASSERT(wglMakeCurrent(dc, context), "Failed to make context current: {0}", GetLastError());

		int status = gladLoadGL();
		MR_CORE_ASSERT(status, "Failed to load Glad");
#endif

		MR_CORE_INFO("OpenGL Info:\n\tVendor: {0}\n\tRenderer: {1}\n\tVersion: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
#ifdef MR_PLATFORM_WINDOWS
		::SwapBuffers(GetDC((HWND)m_WindowHandle));
#endif
	}
}