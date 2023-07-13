#include "Camera.h"

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp):
	m_cameraPos(cameraPos), m_cameraFront(cameraFront), m_cameraUp(cameraUp)
{

}
Camera::~Camera()
{
}
void Camera::Update(GLFWwindow* window, float deltaTime)
{
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

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

	const float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_cameraPos += cameraSpeed * m_cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_cameraPos -= cameraSpeed * m_cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
	}
}
glm::mat4 Camera::GetLookAt() 
{
	return glm::lookAt(m_cameraPos, m_cameraFront + m_cameraPos, m_cameraUp);
}