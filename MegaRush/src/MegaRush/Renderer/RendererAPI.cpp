#include "RendererAPI.h"

#include "MegaRush/Core/Log.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace MegaRush
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case API::None:
				MR_CORE_ASSERT(false, "RendererAPI type required!");
				return nullptr;

			case API::OpenGL:
				return CreateScope<OpenGLRendererAPI>();
		}

		MR_CORE_ASSERT(false, "Unknown RendererAPI type!");
		return nullptr;
	}
}