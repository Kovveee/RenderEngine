#pragma once
// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// C++
#include <vector>
#include <string>

//glm
#include <glm/gtx/transform2.hpp>

// RenderEngine
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

struct Mesh
{
	VertexArray vao;
	VertexBuffer vbo;
	ElementBuffer ibo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	void SetData() {
		vao.Bind();
		vbo.SetBufferData(vertices.size(), &vertices[0]);
		vbo.Bind();
		ibo.SetBufferData(indices.size(), &indices[0]);
		ibo.Bind();
		vao.InitVertexArray();
		vao.Unbind();
		ibo.Unbind();
		vbo.Unbind();
	}
};


class Model
{
public:
	Model(const std::string modelName, const std::string filePath);
	~Model();
	void Draw(Shader* shader, glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos, glm::vec3 objectColor);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void ProcessNode(aiNode* node, const aiScene* scene);
	std::string GetName() const;
	glm::vec3* GetTranslation() { return &m_translation; }
	glm::vec3* GetRotation() { return &m_rotation; }
	glm::vec3* GetScale() { return &m_scale; }
	

private:
	std::vector<Mesh*> meshes;
	std::string m_name;
	glm::vec3 m_translation;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	std::string m_path;
};

