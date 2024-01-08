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
	//void Update(GLFWwindow* window, float deltaTime) { m_cameraController->Update(window, deltaTime); }
	virtual void Update(GLFWwindow* window, float deltaTime) = 0;
	glm::mat4 GetLookAt() { return glm::lookAt(m_cameraPos, m_cameraFront + m_cameraPos, m_cameraUp); }
	glm::vec3 GetPos() { return m_cameraPos; }
	glm::vec3 GetFront() { return m_cameraFront; }
	glm::vec3 GetUp() { return m_cameraUp; }
protected:
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	bool m_firstMove;
private:
};

