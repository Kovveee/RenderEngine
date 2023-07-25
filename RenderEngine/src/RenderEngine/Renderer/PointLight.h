#pragma once
#include "LightSource.h"

class PointLight: public LightSource
{
public:
	PointLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 position);
	~PointLight();
	void SetInShader(Shader* shader) override;
private:
	glm::vec3 m_position;
	float m_constant;
	float m_linear;
	float m_quadratic;
};

