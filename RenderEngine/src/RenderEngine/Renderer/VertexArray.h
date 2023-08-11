#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include <glm/glm.hpp>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void bind();
	void unbind();
	void initVertexArray();
private:
	GLuint m_vaoID;
};

