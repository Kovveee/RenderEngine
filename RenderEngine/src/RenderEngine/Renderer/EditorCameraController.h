#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "CameraControllerBase.h"

class EditorCameraController: public CameraControllerBase
{
public:
	EditorCameraController();
	void Update(GLFWwindow* window ,float deltaTime, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) override;

	float getYaw() { return m_yaw; }
	float getPitch() { return m_pitch; }
private:
	float m_yaw;
	float m_pitch;
	float m_sensitivity;
	float m_lastX;
	float m_lastY;
	float m_speed;
	float m_firstMove;
};

