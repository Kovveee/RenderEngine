#include "Texture.h"

Texture::Texture(const char* imagePath):
	m_textureID(0)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(imagePath, &m_width, &m_height, &m_nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAILED::TO::LOAD::TEXTURE::FROM: "<<imagePath<< std::endl;
	}

	
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}
Texture::~Texture()
{
}
void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}