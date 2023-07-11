#include "VertexArray.h"


VertexArray::VertexArray() 
{
	glGenVertexArrays(1, &m_vaoID);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vaoID);
}
void VertexArray::Bind()
{
	glBindVertexArray(m_vaoID);
}
void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
void VertexArray::InitVertexArray()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 2));
}
