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
#include "Collider.h"


struct Mesh
{
	VertexArray vao;
	VertexBuffer vbo;
	ElementBuffer ibo;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int materialINdex;
	std::vector<Texture*> textures;

	void SetData() {
		vao.bind();
		vbo.setBufferData(vertices.size(), &vertices[0]);
		vbo.bind();
		ibo.SetBufferData(indices.size(), &indices[0]);
		ibo.Bind();
		vao.initVertexArray();
		vao.unbind();
		ibo.Unbind();
		vbo.unbind();
	}
};


class Model
{
public:
	Model(const std::string modelName, const std::string filePath);
	~Model();
	void Draw(Shader* shader, glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos);
	std::string GetName() const { return m_name; };
	glm::vec3* GetTranslation() { return &m_translation; }
	glm::vec3* GetRotation() { return &m_rotation; }
	glm::vec3* GetScale() { return &m_scale; }
	glm::mat4 GetWorld() { return m_world; }
	virtual void HandleMouseInput() {};
	virtual void HandleKeyInput() {};
	Collider collider;

private:
	std::vector<Mesh*> meshes;
	std::vector<glm::vec3> positions;
	std::string m_name;
	glm::vec3 m_translation;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	std::string m_directory;
	glm::mat4 m_world;
	glm::vec3 m_transform;

	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture*> ProcessMaterial(aiMaterial* material, const aiScene* scene, Mesh* mesh);
	void ProcessNode(aiNode* node, const aiScene* scene);
	bool isTextureLoaded(aiString name, Mesh* mesh);
};

