#include "PointLight.h"

PointLight::PointLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 position):
	LightSource(lightId, ambientColor, diffuseColor, specularColor), m_position(position)
{
	m_name = "pointLights[" + std::to_string(m_lightId) + "]";
	m_constant = 1.0f;
	m_linear = 0.09f;
	m_quadratic = 0.032f;
}
PointLight::~PointLight()
{
}
void PointLight::SetInShader(Shader* shader)
{
	
	shader->UseProgram();
	SetColors(shader);
	shader->InitUniformVariable(m_name +".position");
	shader->InitUniformVariable(m_name + ".constant");
	shader->InitUniformVariable(m_name + ".linear");
	shader->InitUniformVariable(m_name + ".quadratic");
	shader->setLightColor(m_name, m_ambient, m_diffuse, m_diffuse);
	shader->setUniform((m_name + ".position").c_str(), m_position);
	shader->setUniform((m_name + ".constant").c_str(), m_constant);
	shader->setUniform((m_name + ".linear").c_str(), m_linear);
	shader->setUniform((m_name + ".quadratic").c_str(), m_quadratic);
	shader->UnuseProgram();
}