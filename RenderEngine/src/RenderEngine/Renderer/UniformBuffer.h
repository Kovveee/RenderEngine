#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class UniformBuffer
{
public:
	UniformBuffer();
	void SetBufferData(unsigned int size, unsigned int indexBlock);
	void SetUniform(unsigned int offset, unsigned int size, void* data);
	void Bind();
	void UnBind();
private:
	GLuint m_bufferID;
};

