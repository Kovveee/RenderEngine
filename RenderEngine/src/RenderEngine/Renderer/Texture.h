#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include <string>

class Texture
{
public:
	Texture(std::string imagePath, std::string type);
	~Texture();
	void Bind();
	void Bind(unsigned int slot);
	void UnBind();
	void UnBind(unsigned int slot);
	const std::string GetType();
	unsigned int GetID();
	const std::string GetPath();
private:
	std::string m_type;
	std::string m_path;
	unsigned int m_textureID;
	int m_width;
	int m_height;
	int m_nrChannels;
	unsigned char* data;
};

