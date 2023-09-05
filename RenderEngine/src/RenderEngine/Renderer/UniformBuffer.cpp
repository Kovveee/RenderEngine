#include "UniformBuffer.h"
UniformBuffer::UniformBuffer()
{
	glGenBuffers(1, &m_bufferID);
}
void UniformBuffer::SetBufferData(unsigned int size, unsigned int indexBlock)
{
	Bind();
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	UnBind();
	glBindBufferRange(GL_UNIFORM_BUFFER, indexBlock, m_bufferID, 0, size);
}
void UniformBuffer::SetUniform(unsigned int offset, unsigned int size, void* data)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	UnBind();
}
void UniformBuffer::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
}
void UniformBuffer::UnBind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}