#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>
#include <string>
#include <dds_loader.h>

class Texture
{
public:
	Texture(std::string imagePath, std::string type);
	void bind();
	void bind(unsigned int slot);
	void unBind();
	void unBind(unsigned int slot);
	const std::string getType() { return m_type; }
	const unsigned int getID() { return m_textureID;  }
	const std::string getPath() { return m_path; }
private:
	std::string m_type;
	std::string m_path;
	unsigned int m_textureID;
	int m_width;
	int m_height;
	int m_nrChannels;
	unsigned char* data = NULL;
	DDS_TEXTURE* dds_data = NULL;
	bool isDDS = false;;
};

