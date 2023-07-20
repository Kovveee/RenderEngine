#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_bufferID);
} 
VertexBuffer::~VertexBuffer() 
{
	glDeleteBuffers(1, &m_bufferID);
}
void VertexBuffer::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
}
void VertexBuffer::Unbind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VertexBuffer::SetBufferData(const unsigned int count, const Vertex* vertex)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}