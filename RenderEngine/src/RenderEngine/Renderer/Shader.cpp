#include "Shader.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath) 
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

	InitUniformVariable("worldMat");
	InitUniformVariable("viewMat");
	InitUniformVariable("projMat");
	InitUniformVariable("worldIT");
	InitUniformVariable("cameraPos");

	InitUniformVariable("material.ambient");
	InitUniformVariable("material.diffuse");
	InitUniformVariable("material.specular");
	InitUniformVariable("material.shininess");

	InitUniformVariable("light.ambient");
	InitUniformVariable("light.diffuse");
	InitUniformVariable("light.specular");
	InitUniformVariable("light.position");

	InitUniformVariable("pointLightNum");
	InitUniformVariable("dirLightNum");

}
Shader::~Shader() 
{
}
void Shader::UseProgram() 
{
	glUseProgram(m_programID);
}
void Shader::UnuseProgram()
{
	glUseProgram(0);
}
void Shader::InitUniformVariable(std::string name) {
	m_uniforms[name] = glGetUniformLocation(m_programID, name.c_str());
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
template<>
void Shader::setUniform<glm::mat4>(const char* name, glm::mat4 value)
{
	glUniformMatrix4fv(m_uniforms[name], 1, GL_FALSE, glm::value_ptr(value));
}
template<>
void Shader::setUniform<int>(const char* name, int value)
{
	glUniform1i(m_uniforms[name],value);
}
template<>
void Shader::setUniform<float>(const char* name, float value)
{
	glUniform1f(m_uniforms[name], value);
}

void Shader::setWVP(glm::mat4 worldMat, glm::mat4 viewMat, glm::mat4 projMat)
{
	glUniformMatrix4fv(m_uniforms["worldMat"], 1, GL_FALSE, glm::value_ptr(worldMat));
	glUniformMatrix4fv(m_uniforms["viewMat"], 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(m_uniforms["projMat"], 1, GL_FALSE, glm::value_ptr(projMat));
	glUniformMatrix4fv(m_uniforms["worldIT"], 1, GL_FALSE, glm::value_ptr(glm::inverse(glm::transpose(worldMat))));
}



void Shader::setMaterial(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float shininess)
{
	setUniform("material.ambient", ambientColor);
	setUniform("material.diffuse", diffuseColor);
	setUniform("material.specular", specularColor);
	setUniform("material.shininess", shininess);

}
void Shader::setLightColor(std::string name, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor)
{
	setUniform((name +".ambient").c_str(), ambientColor);
	setUniform((name+".diffuse").c_str(), diffuseColor);
	setUniform((name+".specular").c_str(), specularColor);
}
void Shader::setCameraPos(glm::vec3 cameraPos)
{
	setUniform("cameraPos", cameraPos);
}
