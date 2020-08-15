#include "GraphicsContext.h"
#include "RendererAPI.h"

#include "MegaRush/Core/Log.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace MegaRush
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				MR_CORE_ASSERT(false, "A RendererAPI is required!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return CreateScope<OpenGLContext>(window);
		}

		MR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}