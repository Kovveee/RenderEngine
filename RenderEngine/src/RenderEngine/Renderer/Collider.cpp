#include "Collider.h"

#include <iostream>

Collider::Collider():
	minX(0), maxX(0), minY(0), maxY(0), minZ(0), maxZ(0)
{
	
}
void Collider::BuildCollider(std::vector<glm::vec3> vertices)
{
	points.clear();
	minX = vertices[0].x;
	maxX = vertices[0].x;
	minY = vertices[0].y;
	maxY = vertices[0].y;
	minZ = vertices[0].z;
	maxZ = vertices[0].z;
	for(int i = 0; i < vertices.size(); ++i)
	{
		if (minX > vertices[i].x)
			minX = vertices[i].x;
		else if (maxX < vertices[i].x)
			maxX = vertices[i].x;
		else if (minY > vertices[i].y)
			minY = vertices[i].y;
		else if (maxY < vertices[i].y)
			maxY = vertices[i].y;
		else if (minZ > vertices[i].z)
			minZ = vertices[i].z;
		else if (maxZ < vertices[i].z)
			maxZ = vertices[i].z;
	}
}
bool Collider::CheckCollision(Collider collider)
{ 
	return (
		minX <= collider.maxX &&
		maxX >= collider.minX &&
		minY <= collider.maxY &&
		maxY >= collider.minY &&
		minZ <= collider.maxZ &&
		maxZ >= collider.minZ);
}