#pragma once
#include "LightSource.h"

class DirectionalLight: public LightSource
{
public:
	DirectionalLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction);
	~DirectionalLight();

	void SetInShader(Shader* shader) override;
private:
	glm::vec3 m_direction;
};

