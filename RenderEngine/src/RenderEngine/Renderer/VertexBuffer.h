#pragma once

#include "Vertex.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class VertexBuffer
{
public:
	VertexBuffer(const unsigned int count, const Vertex* vertex);
	~VertexBuffer();
	void Bind();
	void Unbind();
private:
	GLuint m_bufferID;

};

