#include "DirectionalLight.h"

unsigned int DirectionalLight::Count = 0;

DirectionalLight::DirectionalLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction):
	LightSource(lightId, ambientColor, diffuseColor, specularColor), m_direction(direction)
{
	m_name = "directionalLights[" + std::to_string(m_lightId) + "]";
	m_data.ambient = glm::vec4(m_ambient,1.0);
	m_data.diffuse = glm::vec4( m_diffuse,1.0);
	m_data.direction = glm::vec4(m_direction,1.0);
	m_data.specular = glm::vec4(m_specular,1.0);
}
DirectionalLight::~DirectionalLight()
{
	
}
void DirectionalLight::SetInShader(Shader* shader)
{
	shader->useProgram();
	SetColors(shader);
	shader->initUniformVariable(m_name + ".direction");
	shader->setLightColor(m_name, m_ambient, m_diffuse, m_specular);
	shader->setUniform((m_name + ".direction").c_str(), m_direction);
	shader->unuseProgram();
}
void* DirectionalLight::GetData()
{	
	return  &m_data;
}