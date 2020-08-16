#include "Shader.h"

#include "MegaRush/Core/Log.h"

#include "MegaRush/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace MegaRush
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				MR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(filepath);
		}

		MR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& geometrySrc, const std::string& fragmentSrc)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				MR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;

			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLShader>(name, vertexSrc, geometrySrc, fragmentSrc);
		}

		MR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}