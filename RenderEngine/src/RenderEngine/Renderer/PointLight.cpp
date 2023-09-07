#include "PointLight.h"

unsigned int PointLight::Count = 0;

PointLight::PointLight(unsigned int lightId, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 position):
	LightSource(lightId, ambientColor, diffuseColor, specularColor), m_position(position)
{
	m_name = "pointLights[" + std::to_string(m_lightId) + "]";
	m_constant = 1.0f;
	m_linear = 0.09f;
	m_quadratic = 0.032f;

	m_data.ambient = glm::vec4(m_ambient, 1.0);
	m_data.diffuse = glm::vec4(m_diffuse, 1.0);
	m_data.specular = glm::vec4(m_specular, 1.0);
	m_data.position = glm::vec4(m_position, 1.0);
	m_data.constant = m_constant;
	m_data.linear = m_linear;
	m_data.quadratic = m_quadratic;
}
PointLight::~PointLight()
{
}
void PointLight::SetInShader(Shader* shader)
{
	
	shader->useProgram();
	SetColors(shader);
	shader->initUniformVariable(m_name +".position");
	shader->initUniformVariable(m_name + ".constant");
	shader->initUniformVariable(m_name + ".linear");
	shader->initUniformVariable(m_name + ".quadratic");
	shader->setLightColor(m_name, m_ambient, m_diffuse, m_diffuse);
	shader->setUniform((m_name + ".position").c_str(), m_position);
	shader->setUniform((m_name + ".constant").c_str(), m_constant);
	shader->setUniform((m_name + ".linear").c_str(), m_linear);
	shader->setUniform((m_name + ".quadratic").c_str(), m_quadratic);
	shader->unuseProgram();
}
void* PointLight::GetData()
{
	return &m_data;
}