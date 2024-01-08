#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "CameraControllerBase.h"


class Camera
{
public:
	Camera() {};
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
		:m_cameraPos(cameraPos), m_cameraFront(cameraFront), m_cameraUp(cameraUp), m_firstMove(true) {}
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, CameraControllerBase* cameraController)
		:m_cameraPos(cameraPos), m_cameraFront(cameraFront), m_cameraUp(cameraUp), m_firstMove(true), m_cameraController(cameraController) {}
	void Update(GLFWwindow* window, float deltaTime) { m_cameraController->Update(window, deltaTime, m_cameraPos, m_cameraFront, m_cameraUp); }
	glm::mat4 GetLookAt() { return glm::lookAt(m_cameraPos, m_cameraFront + m_cameraPos, m_cameraUp); }
	glm::vec3 GetPos() { return m_cameraPos; }
	glm::vec3 GetFront() { return m_cameraFront; }
	glm::vec3 GetUp() { return m_cameraUp; }
	void setController(CameraControllerBase* cameraController) { m_cameraController = cameraController; }
protected:
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	bool m_firstMove;
private:
	CameraControllerBase* m_cameraController;
};

