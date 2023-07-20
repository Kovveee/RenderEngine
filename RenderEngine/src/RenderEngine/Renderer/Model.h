#pragma once
// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// C++
#include <vector>
#include <string>

// RenderEngine
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"


struct Mesh
{
	unsigned int VAO, IBO, VBO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};


class Model
{
public:
	Model(const std::string filePath);
	void Draw(Shader* shader, glm::mat4 worldMat, glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos, glm::vec3 objectColor);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void ProcessNode(aiNode* node, const aiScene* scene);
private:
	std::vector<Mesh> meshes;
	
};

