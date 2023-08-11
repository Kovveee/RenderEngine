#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

class EditorCamera: public Camera
{
public:
	EditorCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
	void Update(GLFWwindow* window ,float deltaTime) override;
private:
	float m_yaw;
	float m_pitch;
	float m_sensitivity;
	float m_lastX;
	float m_lastY;
	float m_speed;
};

