#pragma once
#include "Camera.h"
#include "Model.h"

class GameCamera: public Camera
{
public:
	GameCamera();
	void Update(float deltaTime, Model* model);
	void Update(GLFWwindow* window, float deltaTime) override;
private:
	
};

