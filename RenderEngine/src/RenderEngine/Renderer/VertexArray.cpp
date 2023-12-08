#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vaoID);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vaoID);
}
void VertexArray::bind()
{
	glBindVertexArray(m_vaoID);
}
void VertexArray::unbind()
{
	glBindVertexArray(0);
}
void VertexArray::initVertexArray()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 2));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((sizeof(glm::vec3) * 2) + sizeof(glm::vec2)));
}
