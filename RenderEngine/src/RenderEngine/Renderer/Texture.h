#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

class Texture
{
public:
	Texture(const char* imagePath);
	~Texture();
	void Bind();
	void UnBind();
private:
	unsigned int m_textureID;
	int m_width;
	int m_height;
	int m_nrChannels;
	unsigned char* data;
};

