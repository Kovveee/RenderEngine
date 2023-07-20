#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class ElementBuffer
{
public:
	ElementBuffer();
	~ElementBuffer();
	void Bind();
	void Unbind();
	void SetBufferData(const unsigned int count, const unsigned int* indices);
private:
	GLuint m_bufferID;
};

