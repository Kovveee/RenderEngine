#include "Skybox.h"

Skybox* Skybox::s_Skybox = NULL;

Skybox::Skybox(std::vector<std::string> &texturePaths)
	:m_texturePaths(texturePaths)
{
	s_Skybox = this;
	LoadTexture();

	m_vao.bind();
	m_vbo.bind();
	m_ibo.Bind();
	m_vbo.setBufferData(8, &m_skyboxData[0]);
	m_ibo.SetBufferData(36, &m_skyboxIndices[0]);
	m_vao.initVertexArray();

	m_skyboxShader = new Shader(shaderFilePath + "skybox.vert", shaderFilePath + "skybox.frag");
	m_skyboxShader->BindUniformBlock(0, "Matrices");
}
Skybox::~Skybox()
{
	delete m_skyboxShader;
}
void Skybox::Draw()
{
	m_skyboxShader->useProgram();
	m_skyboxShader->setWorldMat(glm::mat4(1));
	glDepthMask(GL_FALSE);
	m_vao.bind();
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
	m_skyboxShader->unuseProgram();
}
void Skybox::LoadTexture()
{
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	int width, height, nrChannels;
	for(unsigned int i = 0; i < 6; ++i)
	{
		unsigned char* data = stbi_load(m_texturePaths[i].c_str(), &width, &height, &nrChannels, 0);
		if(data)
		{
			GLenum format = GL_RGB;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		}
		else
		{
			std::cout << "ERROR::LOADING::SKYBOX::TEXTURE" << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
void Skybox::SetTexture(std::vector<std::string>& texturePaths)
{
	m_texturePaths = texturePaths;
	LoadTexture();
}
