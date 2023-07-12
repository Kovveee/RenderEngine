#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>


class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void UseProgram();
	void InitUniformVariable(const char* name);
	template<typename T>
	void setUniform(const char* name, T value);
	template<>
	void setUniform<glm::vec2>(const char* name, glm::vec2 value);
	template<>
	void setUniform<glm::vec3>(const char* name, glm::vec3 value);
	template<>
	void setUniform<glm::vec4>(const char* name, glm::vec4 value);



private:
	GLuint m_programID;
	std::map<const char*, int> m_uniforms;
};

