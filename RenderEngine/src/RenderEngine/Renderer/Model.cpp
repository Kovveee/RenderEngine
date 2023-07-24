#include "Model.h"


Model::Model(const std::string modelName , const std::string filePath):
	m_name(modelName), m_translation(glm::vec3(0.f, 0.f, 0.f)), m_rotation(glm::vec3(0.f,0.f,0.f)), m_scale(glm::vec3(1.f, 1.f, 1.f))
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate| aiProcess_GenSmoothNormals);

	if(scene == nullptr)
	{
		std::cout << "ASSIMP::LOADING::ERROR::" << importer.GetErrorString() << std::endl;
		return;
	}

	ProcessNode(scene->mRootNode,scene);	 
}
Model::~Model()
{
	for(Mesh* mesh: meshes)
	{
		delete mesh;
	}
}
void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(ProcessMesh(mesh, scene));
	}
	for(unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}
 Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	Mesh* meshToAdd = new Mesh();
	for(unsigned int i  = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;	
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;

		vertex.normals = vector;
		vertex.texture = glm::vec2(1.0f);
		meshToAdd->vertices.push_back(vertex);
	}
	for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		if (face.mNumIndices < 3)
			continue;
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			meshToAdd->indices.push_back(face.mIndices[j]);
		}
	}

	meshToAdd->SetData();
 	return meshToAdd;
}

void Model::Draw(Shader* shader, glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos, glm::vec3 objectColor)
{
	shader->UseProgram();
	shader->setCameraPos(cameraPos);
	glm::mat4 world = glm::rotate(glm::radians(m_rotation.z), glm::vec3(0.f, 0.f, 1.f)) * glm::rotate(glm::radians(m_rotation.y), glm::vec3(0.f, 1.f, 0.f)) * glm::rotate(glm::radians(m_rotation.x), glm::vec3(1.f, 0.f,0.f)) * glm::translate(m_translation) * glm::scale(m_scale) * glm::mat4(1);
	shader->setWVP(world, view, proj);
	shader->setLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 3.f, 2.f));
	shader->setUniform("objectColor", objectColor);


	for(unsigned int i = 0; i < meshes.size(); ++i)
	{
		meshes[i]->vao.Bind();
		glDrawElements(GL_TRIANGLES, meshes[i]->indices.size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}

	shader->UnuseProgram();
}
std::string Model::GetName() const
{
	return m_name;
}

