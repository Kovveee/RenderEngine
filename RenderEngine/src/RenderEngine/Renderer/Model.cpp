#include "Model.h"


Model::Model(const std::string modelName , const std::string filePath):
	m_name(modelName), m_translation(glm::vec3(0.f, 0.f, 0.f)), m_rotation(glm::vec3(0.f,0.f,0.f)), m_scale(glm::vec3(1.f, 1.f, 1.f))
{
	Assimp::Importer importer;

	m_directory = filePath.substr(0, filePath.find_last_of('\\'));
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate| aiProcess_GenSmoothNormals);

	if(scene == nullptr)
	{
		std::cout << "ASSIMP::LOADING::ERROR::" << importer.GetErrorString() << std::endl;
		return;
	}

	ProcessNode(scene->mRootNode,scene);	
	collider.BuildCollider(positions);
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
std::vector<Texture*> Model::ProcessMaterial(aiMaterial* material, const aiScene* scene, Mesh* mesh)
{
	std::vector<Texture*> texturesToAdd;
	aiString textureName;
	for(int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i)
	{
		material->GetTexture(aiTextureType_DIFFUSE, i, &textureName);		
		if(isTextureLoaded(textureName, mesh) == false)
		{
			std::string textureNameTemp = std::string(textureName.C_Str());
			Texture* textureToAdd = new Texture(m_directory + "\\" + textureNameTemp.substr(textureNameTemp.find_last_of('/') + 1, textureNameTemp.length()), "diffuse");
			texturesToAdd.push_back(textureToAdd);
		}
	}
	for (int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); ++i)
	{
		material->GetTexture(aiTextureType_SPECULAR, i, &textureName);
		if (isTextureLoaded(textureName, mesh) == false)
		{
			std::string textureNameTemp = std::string(textureName.C_Str());
			Texture* textureToAdd = new Texture(m_directory + "\\" + textureNameTemp.substr(textureNameTemp.find_last_of('/') + 1, textureNameTemp.length()), "specular");
			texturesToAdd.push_back(textureToAdd);
		}
	}
	return texturesToAdd;
}
bool Model::isTextureLoaded(aiString name, Mesh* mesh) 
{
	for(Texture* tex: mesh->textures)
	{
		if (tex->getPath() == name.C_Str())
			return true;
	}
	return false;
}


 Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	Mesh* meshToAdd = new Mesh();
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	meshToAdd->textures = ProcessMaterial(material, scene, meshToAdd);

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

		if (mesh->HasTextureCoords(0))
		{
			glm::vec2 texture;
			texture.x = mesh->mTextureCoords[0][i].x;
			texture.y = mesh->mTextureCoords[0][i].y;
			vertex.texture = texture;
		}
		positions.push_back(vertex.position);
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

void Model::Draw(Shader* shader, glm::vec3 cameraPos)
{
	shader->useProgram();
	shader->setCameraPos(cameraPos);
	glm::vec4 transformTemp = glm::vec4(1) * glm::translate(m_translation) * (glm::rotate(glm::radians(m_rotation.z), glm::vec3(0.f, 0.f, 1.f)) * glm::rotate(glm::radians(m_rotation.y), glm::vec3(0.f, 1.f, 0.f)) * glm::rotate(glm::radians(m_rotation.x), glm::vec3(1.f, 0.f, 0.f))) * glm::scale(m_scale) * glm::mat4(1);
	
	m_world = glm::translate(m_translation) * (glm::rotate(glm::radians(m_rotation.z), glm::vec3(0.f, 0.f, 1.f)) * glm::rotate(glm::radians(m_rotation.y), glm::vec3(0.f, 1.f, 0.f)) * glm::rotate(glm::radians(m_rotation.x), glm::vec3(1.f, 0.f, 0.f))) * glm::scale(m_scale) * glm::mat4(1);
	m_transform = glm::vec3(transformTemp.x, transformTemp.y, transformTemp.z);
	shader->setWorldMat(m_world);

	for(unsigned int i = 0; i < meshes.size(); ++i)
	{
		for (unsigned int j = 0; j < meshes[i]->textures.size(); ++j)
		{
			if (meshes[i]->textures[j]->getType() == "diffuse")
			{
				shader->initUniformVariable("material.diffuse");
				shader->setUniform("material.diffuse", 0);
				meshes[i]->textures[j]->bind(j);
			}
			else
			{
				shader->initUniformVariable("material.specular");
				shader->setUniform("material.specular", 1);
				meshes[i]->textures[j]->bind(j);
			}
		}
		meshes[i]->vao.bind();
		glDrawElements(GL_TRIANGLES, meshes[i]->indices.size(), GL_UNSIGNED_INT, NULL);
		for (unsigned int j = 0; j < meshes[i]->textures.size(); ++j)
		{
			meshes[i]->textures[j]->unBind(j);
		}
		glBindVertexArray(0);
	}
	positions.clear();
	for (Mesh* mesh : meshes)
	{
		for (int i = 0; i < mesh->vertices.size(); ++i)
		{
			glm::vec4 vertex = m_world * glm::vec4(mesh->vertices[i].position.x, mesh->vertices[i].position.y, mesh->vertices[i].position.z, 1);
			positions.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
		}
	}
	collider.BuildCollider(positions);
	shader->unuseProgram();
}	

