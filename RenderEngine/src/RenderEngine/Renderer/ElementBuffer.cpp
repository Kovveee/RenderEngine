#include "ElementBuffer.h"


ElementBuffer::ElementBuffer()
{
	glGenBuffers(1, &m_bufferID);
}
ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &m_bufferID);
}
void ElementBuffer::Bind() 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}
void ElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void ElementBuffer::SetBufferData(const unsigned int count, const unsigned int* indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}