#include "VertexBuffer.h"
#include <iostream>

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_bufferID);
} 
VertexBuffer::~VertexBuffer() 
{
	glDeleteBuffers(1, &m_bufferID);
}
void VertexBuffer::bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}
void VertexBuffer::unbind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VertexBuffer::setBufferData(const unsigned int count, const Vertex* vertex)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), vertex, GL_STATIC_DRAW);
}