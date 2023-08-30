#include "EditorCamera.h"

EditorCamera::EditorCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp):
	Camera(cameraPos,cameraFront, cameraUp)
{
	m_lastX = 0;
	m_lastY = 0;
	m_yaw = -90.f;
	m_pitch = 0.f;
	m_speed = 2.5f;
	m_sensitivity = 0.05f;
}
void EditorCamera::Update(GLFWwindow* window, float deltaTime)
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
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_firstMove = true;
	}
	
}