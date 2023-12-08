#pragma once

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 texture;
	glm::vec3 tagent;
};