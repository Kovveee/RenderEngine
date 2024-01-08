#pragma once


class CameraControllerBase {
public:
	virtual void Update(GLFWwindow* window, float deltaTime) = 0;
private:
};