#include "Model.h"

Model::Model(const std::string filePath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_Triangulate| aiProcess_GenSmoothNormals);



	if(scene == nullptr)
	{
		std::cout << "ASSIMP::LOADING::ERROR::" << importer.GetErrorString() << std::endl;
		return;
	}
	//meshes.resize(scene->mNumMeshes);

	ProcessNode(scene->mRootNode,scene);	 
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
 Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	Mesh meshToAdd;
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
		meshToAdd.vertices.push_back(vertex);
	}
	for(unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		if (face.mNumIndices < 3)
			continue;
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			meshToAdd.indices.push_back(face.mIndices[j]);
		}
	}

	glGenVertexArrays(1, &meshToAdd.VAO);
	glBindVertexArray(meshToAdd.VAO);
	glGenBuffers(1, &meshToAdd.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, meshToAdd.VBO);
	glBufferData(GL_ARRAY_BUFFER, meshToAdd.vertices.size() * sizeof(Vertex), &meshToAdd.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &meshToAdd.IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshToAdd.IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshToAdd.indices.size() *sizeof(unsigned int), &meshToAdd.indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));

	return meshToAdd;
}

void Model::Draw(Shader* shader, glm::mat4 worldMat, glm::mat4 view, glm::mat4 proj, glm::vec3 cameraPos, glm::vec3 objectColor)
{
	shader->UseProgram();
	shader->setCameraPos(cameraPos);
	shader->setWVP(worldMat, view, proj);
	shader->setLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 3.f, 2.f));
	shader->setUniform("objectColor", objectColor);


	for(unsigned int i = 0; i < meshes.size(); ++i)
	{
		glBindVertexArray(meshes[i].VAO);
		glDrawElements(GL_TRIANGLES, meshes[i].indices.size(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}

	shader->UnuseProgram();
}
