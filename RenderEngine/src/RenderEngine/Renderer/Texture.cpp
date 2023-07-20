#include "Texture.h"

Texture::Texture(std::string imagePath, std::string type) :
	m_textureID(0), m_type(type), m_path(imagePath)
{

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	//data = stbi_load(imagePath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	/*if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAILED::TO::LOAD::TEXTURE::FROM: "<<imagePath<< std::endl;
	}*/

	
	glBindTexture(GL_TEXTURE_2D, 0);
	//stbi_image_free(data);
}
Texture::~Texture()
{
}
void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
const std::string Texture::GetType()
{
	return m_type;
}
const unsigned int* Texture::GetID()
{
	return &m_textureID;
}
const std::string Texture::GetPath()
{
	return m_path;
}