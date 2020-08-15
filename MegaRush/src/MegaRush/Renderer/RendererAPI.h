#pragma once

#include "MegaRush/Core/Base.h"
#include <glm/glm.hpp>

namespace MegaRush
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		static Scope<RendererAPI> Create();
		static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}