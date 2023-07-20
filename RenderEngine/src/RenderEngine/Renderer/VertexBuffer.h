#pragma once

#include "Vertex.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void Bind();
	void Unbind();
	void SetBufferData(const unsigned int count, const Vertex* vertex);
private:
	GLuint m_bufferID;

};

