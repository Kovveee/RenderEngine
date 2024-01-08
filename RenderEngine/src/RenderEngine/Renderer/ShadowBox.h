#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "Camera.h"

#include <vector>

class ShadowBox
{
public:
	ShadowBox(EditorCameraController& camera, glm::mat4 lightViewMatrix, float screenWidth, float screenHeight);
	
	void Update();
	glm::vec3 getCenter();
	float getWidth();
	float getHeight();
	float getLength();

private:
	float m_offset = 10;
	glm::vec3 m_up = glm::vec3(0, 1.f, 0);
	glm::vec3 m_forward = glm::vec3(0, 0, -1);
	float m_shadowDistance = 100;

	float m_screenWidth;
	float m_screenHeight;

	EditorCameraController m_camera;

	glm::mat4 m_lightViewMatrix;

	float m_minX, m_maxX;
	float m_minY, m_maxY;
	float m_minZ, m_maxZ;

	float m_farHeight, m_farWidth, m_nearHeight, m_nearWidth;


	std::vector<glm::vec3> calculateFrustumVertices(glm::mat4 rotation, glm::vec3 forwardVector, glm::vec3 centerNear, glm::vec3 centerFar);
	glm::vec3 calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width);
	glm::mat4 calculateCameraRotationMatrix();
	void calculateWidthAndHeight();
	float getAspectRatio();

};

