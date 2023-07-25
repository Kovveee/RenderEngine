#pragma once

// C++
#include <string>

// RenderEngine
#include "Shader.h"

// GLM
#include <glm/glm.hpp>

class LightSource
{
public:
	virtual void SetInShader(Shader* shader) = 0;
protected:
	LightSource(unsigned int lightId, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular): m_lightId(lightId), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular){}

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	const unsigned int m_lightId;
	std::string m_name;

	void SetColors(Shader* shader)
	{
		shader->InitUniformVariable(m_name + ".ambient");
		shader->InitUniformVariable(m_name + ".diffuse");
		shader->InitUniformVariable(m_name + ".specular");
	}
private:
	
};