#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

const float YAW = -90.f;
const float PITCH = 0.f;
const float SENSITIVITY = 0.05f;
const float SPEED = 2.5f;
const glm::vec3 CAMERAPOS = glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 CAMERAFRONT = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 CAMERUP = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera
{
public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
	~Camera();
	void Update(GLFWwindow* window ,float deltaTime);
	glm::mat4 GetLookAt();
	glm::vec3 GetPos();
private:
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	float m_lastX;
	float m_lastY;
	float m_yaw;
	float m_pitch;
	float m_sensitivity;
	float m_speed;
	bool m_firstMove;

	void MouseInputHandler(GLFWwindow* window);
	void KeyboardInputHandler(GLFWwindow* window, float deltaTime);

};

