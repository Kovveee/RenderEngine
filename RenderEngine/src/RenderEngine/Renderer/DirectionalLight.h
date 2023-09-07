#pragma once
#include "LightSource.h"

struct DirectionalLightData
{
	glm::vec4 direction;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
};

class DirectionalLight: public LightSource
{
public:
	DirectionalLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction);
	~DirectionalLight();

	void SetInShader(Shader* shader) override;

	const static unsigned int Size = 4 * sizeof(glm::vec4);

	static unsigned int Count;


	void* GetData() override;

private:
	glm::vec3 m_direction;
	DirectionalLightData m_data;
	
};

