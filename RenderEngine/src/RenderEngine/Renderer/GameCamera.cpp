#include "GameCamera.h"


GameCamera::GameCamera()
{
	m_cameraPos = glm::vec3(0, 10, -5);
	m_cameraFront = glm::vec3(0, -1, 1);
	m_cameraUp = glm::vec3(0, 1, 0);
}
void GameCamera::Update(float deltaTime, Model* model)
{
	m_cameraPos = *model->GetTranslation() - glm::vec3(0, -150, 140);
}
void GameCamera::Update(GLFWwindow* window, float deltaTime)
{

}