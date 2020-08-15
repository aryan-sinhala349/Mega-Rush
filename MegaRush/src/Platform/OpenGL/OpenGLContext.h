#pragma once

#include "MegaRush/Renderer/GraphicsContext.h"

namespace MegaRush
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(void* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		void* m_WindowHandle;
	};
}