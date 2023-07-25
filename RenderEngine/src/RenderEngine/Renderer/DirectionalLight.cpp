#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction):
	LightSource(lightId, ambientColor, diffuseColor, specularColor), m_direction(direction)
{
	
}
DirectionalLight::~DirectionalLight()
{
	
}
void DirectionalLight::SetInShader(Shader* shader)
{
	shader->UseProgram();
	SetColors(shader);
	shader->InitUniformVariable("directionalLights[" + std::to_string(m_lightId) + "].direction");
	shader->setLightColor("directionalLights[" + std::to_string(m_lightId) + "]", m_ambient, m_diffuse, m_diffuse);
	shader->setUniform(("directionalLights[" + std::to_string(m_lightId) + "].direction").c_str(), m_direction);
	shader->UnuseProgram();
}