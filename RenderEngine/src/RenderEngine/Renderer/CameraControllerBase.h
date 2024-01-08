#pragma once


class CameraControllerBase {
public:
	CameraControllerBase() {};
	virtual void Update(GLFWwindow* window, float deltaTime, glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp) = 0;
private:
};