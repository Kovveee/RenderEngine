#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction):
	LightSource(lightId, ambientColor, diffuseColor, specularColor), m_direction(direction)
{
	m_name = "directionalLights[" + std::to_string(m_lightId) + "]";
}
DirectionalLight::~DirectionalLight()
{
	
}
void DirectionalLight::SetInShader(Shader* shader)
{
	shader->UseProgram();
	SetColors(shader);
	shader->InitUniformVariable(m_name + ".direction");
	shader->setLightColor(m_name, m_ambient, m_diffuse, m_diffuse);
	shader->setUniform((m_name + ".direction").c_str(), m_direction);
	shader->UnuseProgram();
}