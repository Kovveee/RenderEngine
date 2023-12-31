#include "Texture.h"

Texture::Texture(std::string imagePath, std::string type) :
	m_textureID(0), m_type(type), m_path(imagePath)
{
	isDDS = imagePath.find(".dds") != imagePath.npos ? true : false;
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (isDDS) {
		dds_data = new DDS_TEXTURE();
		load_dds_from_file((char*)imagePath.c_str(), &dds_data, true);
		m_width = dds_data->width;
		m_height = dds_data->height;
		m_nrChannels = dds_data->channels;
	}
	else {
		stbi_set_flip_vertically_on_load(true);
		data = stbi_load(imagePath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	}

	if (data || dds_data)
	{
		if (type == "diffuse") {
			GLenum format = GL_RGB;
			if (m_nrChannels == 1)
				format = GL_RED;
			else if (m_nrChannels == 4)
				format = GL_RGBA;
			if(isDDS) 	glCompressedTexImage2D(GL_TEXTURE_2D, 0, dds_data->format, dds_data->width, 
				dds_data->height, 0, dds_data->sz, dds_data->pixels);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (type == "specular" || type == "normal") {
			GLenum format = GL_RGB;
			if (m_nrChannels == 1)
				format = GL_RED;
			else if (m_nrChannels == 4)
				format = GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		std::cout << "FAILED::TO::LOAD::TEXTURE::FROM: "<<imagePath<< std::endl;
	}

	
	glBindTexture(GL_TEXTURE_2D, 0);
	if (isDDS)
		delete dds_data;
	else
		stbi_image_free(data);
}
void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
void Texture::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
void Texture::unBind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::unBind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, 0);
}
