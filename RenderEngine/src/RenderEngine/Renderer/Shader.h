#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>


class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void UseProgram();

private:
	GLuint m_programID;
};

