#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <string>
#include <vector>
#include <iostream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Vertex.h"
#include "Shader.h"

class Skybox
{
public:
	Skybox(std::vector<std::string> &texturePaths);
	~Skybox();
	void Draw(glm::mat4 viewMat, glm::mat4 projMat);
	void SetTexture(std::vector<std::string> &texturePaths);

private:
	static Skybox* s_Skybox;
	std::vector<std::string> m_texturePaths;
	unsigned int m_textureID;

	VertexArray m_vao;
	VertexBuffer m_vbo;
	ElementBuffer m_ibo;

	Shader* m_skyboxShader;
	
	const std::string shaderFilePath = "..\\RenderEngine\\src\\RenderEngine\\Renderer\\Shaders\\";

	void LoadTexture();

	std::vector<Vertex> m_skyboxData =
	{
		{glm::vec3(-1,1,1), glm::vec3(0,0,-1), glm::vec2(1,1)}, // 0
		{glm::vec3(1,1,1), glm::vec3(0,0,-1), glm::vec2(1,1)}, // 1
		{glm::vec3(-1,-1,1), glm::vec3(0,0,-1), glm::vec2(1,1)}, // 2
		{glm::vec3(1,-1,1), glm::vec3(0,0,-1), glm::vec2(1,1)}, // 3
		{glm::vec3(-1,1,-1), glm::vec3(0,0,-1), glm::vec2(1,1)}, // 4
		{glm::vec3(1,1,-1), glm::vec3(0,0,-1), glm::vec2(1,1)}, // 5
		{glm::vec3(-1,-1,-1), glm::vec3(0,0,-1), glm::vec2(1,1)}, // 6
		{glm::vec3(1,-1,-1), glm::vec3(0,0,-1), glm::vec2(1,1)}, // 7
	};

	std::vector<unsigned int> m_skyboxIndices =
	{
		6,7,5,
		5,4,6,

		6,2,3,
		3,7,6,

		1,3,2,
		2,0,1,

		2,6,4,
		4,0,2,


		1,0,4,
		4,5,1,

		7,3,1,
		7,1,5
	};
};

