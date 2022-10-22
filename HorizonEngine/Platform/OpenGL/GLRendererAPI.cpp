#include "pch.h"
#include "GLRendererAPI.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hzn
{
	GLRendererAPI::GLRendererAPI()
	{
	}

	GLRendererAPI::~GLRendererAPI()
	{

	}

	void GLRendererAPI::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRendererAPI::submitClear()
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRendererAPI::drawElements(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->getElementBuffer()->size(), GL_UNSIGNED_INT, nullptr);
	}

	void GLRendererAPI::drawTriangles(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}