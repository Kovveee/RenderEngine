#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


class Shader
{
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();
	void useProgram();
	void unuseProgram();

	void initUniformVariable(std::string name);
	template<typename T>
	void setUniform(const char* name, T value);
	template<>
	void setUniform<glm::vec2>(const char* name, glm::vec2 value);
	template<>
	void setUniform<glm::vec3>(const char* name, glm::vec3 value);
	template<>
	void setUniform<glm::vec4>(const char* name, glm::vec4 value);
	template<>
	void setUniform<glm::mat4>(const char* name, glm::mat4 value);
	template<>
	void setUniform<int>(const char* name, int value);
	template<>
	void setUniform<unsigned int>(const char* name, unsigned int value);
	template<>
	void setUniform<float>(const char* name, float value);
	template<>
	void setUniform<bool>(const char* name, bool value);

	void setWVP(glm::mat4 worldMat, glm::mat4 viewMat, glm::mat4 projMat);
	void setMaterial(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float shininess);
	void setLightColor(std::string name, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor);
	void setCameraPos(glm::vec3 cameraPos);
	void setWorldMat(glm::mat4 worldMat);
	void BindUniformBlock(unsigned int blockIndex, std::string name);
	void AttachGeometry(std::string geometryPath);

private:
	GLuint m_programID;
	std::map<std::string, int> m_uniforms;
	std::string m_vertexPath;
	std::string m_fragmentPath;
	std::string m_geometryPath;

	bool m_isGeometryAttached = false;

	void CompileShader();
};

