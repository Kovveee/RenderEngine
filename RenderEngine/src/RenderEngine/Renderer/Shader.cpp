#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) 
{
	// Reading file and converting to char*
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();


		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		
	}
	catch (std::ifstream::failure& e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	};

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	

	// Creating the shader program / compiling shaders

	GLuint vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertex);
	glAttachShader(m_programID, fragment);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}
Shader::~Shader() 
{
}
void Shader::UseProgram() 
{
	glUseProgram(m_programID);
}
void Shader::InitUniformVariable(const char* name) {
	m_uniforms[name] = glGetUniformLocation(m_programID, name);
}
template<typename T>
void Shader::setUniform(const char* name, T value) 
{
	std::runtime_error(false);
}
template<>
void Shader::setUniform<glm::vec2>(const char* name, glm::vec2 value)
{
	glUniform2f(m_uniforms[name], value.x, value.y);
}
template<>
void Shader::setUniform<glm::vec3>(const char* name, glm::vec3 value) 
{
	glUniform3f(m_uniforms[name], value.x, value.y, value.z);
}
template<>
void Shader::setUniform<glm::vec4>(const char* name, glm::vec4 value)
{
	glUniform4f(m_uniforms[name], value.x, value.y, value.z, value.w);
}
