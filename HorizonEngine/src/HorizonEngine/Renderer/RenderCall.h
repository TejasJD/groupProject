#pragma once

#ifndef HZN_RENDER_COMMAND_H
#define HZN_RENDER_COMMAND_H

#include "RendererAPI.h"

namespace Hzn
{
	//! class with static member functions that makes calls to the appropriate rendering API.
	class RenderCall
	{
	public:

		inline static void init() { m_Api->init(); }

		inline static void setClearColor(const glm::vec4& color) { m_Api->setClearColor(color); }

		inline static void submitClear() { m_Api->submitClear(); }

		inline static void drawElements(const std::shared_ptr<VertexArray>& vertexArray) { m_Api->drawElements(vertexArray); }

		static RendererAPI* create();

	private:
		static RendererAPI* m_Api;
	};
}

#endif