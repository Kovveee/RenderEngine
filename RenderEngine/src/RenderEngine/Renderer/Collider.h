#pragma once

#include <glm/gtx/transform2.hpp>

#include <vector>

#include "Vertex.h"

class Collider
{
public:
	Collider();
	void BuildCollider(std::vector<glm::vec3> vertices);
	bool CheckCollision(Collider collider);
	float minX, maxX, minY, maxY, minZ, maxZ;
private:
	std::vector<glm::vec3> points;
};

