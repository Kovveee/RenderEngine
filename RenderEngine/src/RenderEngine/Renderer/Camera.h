#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

// TO DO:  Make it better
const float YAW;

class Camera
{
public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
	~Camera();
	void Update(GLFWwindow* window ,float deltaTime);
	glm::mat4 GetLookAt();
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


};

