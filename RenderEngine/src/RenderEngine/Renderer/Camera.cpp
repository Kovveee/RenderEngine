#include "Camera.h"

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp):
	m_cameraPos(cameraPos), m_cameraFront(cameraFront), m_cameraUp(cameraUp)
{
	m_lastX = 0;
	m_lastY = 0;
	m_yaw = YAW;
	m_pitch = PITCH;
	m_speed = SPEED;
	m_sensitivity = SENSITIVITY;
	m_firstMove = true;
}
Camera::~Camera()
{
}
void Camera::Update(GLFWwindow* window, float deltaTime)
{
	MouseInputHandler(window);
	KeyboardInputHandler(window, deltaTime);
}
glm::mat4 Camera::GetLookAt() 
{
	return glm::lookAt(m_cameraPos, m_cameraFront + m_cameraPos, m_cameraUp);
}
void Camera::MouseInputHandler(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		if (m_firstMove)
		{
			m_lastX = xPos;
			m_lastY = yPos;
			m_firstMove = false;
		}

		float xoffset = (xPos - m_lastX) * m_sensitivity;
		float yoffset = (m_lastY - yPos) * m_sensitivity;
		m_lastX = xPos;
		m_lastY = yPos;

		m_yaw += xoffset;
		m_pitch += yoffset;

		if (m_pitch > 89.f)
			m_pitch = 89.f;
		if (m_pitch < -89.f)
			m_pitch = -89.f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		direction.y = sin(glm::radians(m_pitch));
		direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_cameraFront = glm::normalize(direction);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_firstMove = true;
	}
}
void Camera::KeyboardInputHandler(GLFWwindow* window, float deltaTime) 
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_cameraPos += m_speed * deltaTime * m_cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_cameraPos -= m_speed * deltaTime * m_cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_speed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_speed * deltaTime;
	}
}
glm::vec3 Camera::GetPos() {
	return m_cameraPos;
}