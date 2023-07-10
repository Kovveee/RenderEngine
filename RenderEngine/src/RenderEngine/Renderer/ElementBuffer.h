#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class ElementBuffer
{
public:
	ElementBuffer(const unsigned int count, const unsigned int* indices);
	~ElementBuffer();
	void Bind();
	void Unbind();
private:
	GLuint m_bufferID;
};

