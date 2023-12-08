#include "ShadowBox.h"

ShadowBox::ShadowBox(EditorCamera& camera, glm::mat4 lightViewMatrix, float screenWidth, float screenHeight) 
	: m_camera(camera), m_lightViewMatrix(lightViewMatrix), m_screenWidth(screenWidth), m_screenHeight(screenHeight) {}

void ShadowBox::Update(){
	glm::mat4 rotation = calculateCameraRotationMatrix();
	glm::vec3 forwardVector = rotation * glm::vec4(m_forward.x,m_forward.y,m_forward.z,0);

	glm::vec3 toFar = forwardVector * m_shadowDistance;
	glm::vec3 toNear = forwardVector * 0.1f;

	glm::vec3 centerNear = toNear + m_camera.GetPos();
	glm::vec3 centerFar = toFar + m_camera.GetPos();


	std::vector<glm::vec3> points = calculateFrustumVertices(rotation, forwardVector, centerNear, centerFar);

	bool first = false;

	for (glm::vec3 point : points) {
		if (first) {
			m_minX = point.x;
			m_maxX = point.x;
			m_minY = point.y;
			m_maxY = point.y;
			m_minZ = point.z;
			m_maxZ = point.z;
			first = false;
			continue;
		}
		if (point.x > m_maxX) {
			m_maxX = point.x;
		}
		else if (point.x < m_minX) {
			m_minX = point.x;
		}
		if (point.y > m_maxY) {
			m_maxY = point.y;
		}
		else if (point.y < m_minY) {
			m_minY = point.y;
		}
		if (point.z > m_maxZ) {
			m_maxZ = point.z;
		}
		else if (point.z < m_minZ) {
			m_minZ = point.z;
		}
	}
	m_maxZ += m_offset;

	
}
glm::vec3 ShadowBox::getCenter() {
	float x = (m_minX + m_maxX) / 2.f;
	float y = (m_minY + m_maxY) / 2.f;
	float z = (m_minZ + m_maxZ) / 2.f;
	glm::vec4 cen = glm::vec4(x, y, z,1);
	glm::mat4 invertedLight = glm::inverse(m_lightViewMatrix);

	return invertedLight * cen;
}
float ShadowBox::getWidth() {
	return m_maxX - m_minX;
}
float ShadowBox::getHeight() {
	return m_maxY - m_minY;
}
float ShadowBox::getLength() {
	return m_maxZ - m_minZ;
}
std::vector<glm::vec3> ShadowBox::calculateFrustumVertices(glm::mat4 rotation, glm::vec3 forwardVector, glm::vec3 centerNear, glm::vec3 centerFar) {
	glm::vec3 upVector = rotation * glm::vec4(m_up.x,m_up.y,m_up.z, 1);
	glm::vec3 rightVector = glm::cross(forwardVector, upVector); 
	glm::vec3 downVector = glm::vec3(-upVector.x, -upVector.y, -upVector.z);
	glm::vec3 leftVector = glm::vec3(-rightVector.x, -rightVector.y, -rightVector.z);
	glm::vec3 farTop = centerFar +glm::vec3(upVector.x * m_farHeight,
		upVector.y * m_farHeight, upVector.z * m_farHeight);
	glm::vec3 farBottom = centerFar + glm::vec3(downVector.x * m_farHeight,
		downVector.y * m_farHeight, downVector.z * m_farHeight);
	glm::vec3 nearTop = centerNear +glm::vec3(upVector.x * m_nearHeight,
		upVector.y * m_nearHeight, upVector.z * m_nearHeight);
	glm::vec3 nearBottom = centerNear +glm::vec3(downVector.x * m_nearHeight,
		downVector.y * m_nearHeight, downVector.z * m_nearHeight);
	std::vector<glm::vec3> points;
	points.reserve(9);
	points[0] = calculateLightSpaceFrustumCorner(farTop, rightVector, m_farWidth);
	points[1] = calculateLightSpaceFrustumCorner(farTop, leftVector, m_farWidth);
	points[2] = calculateLightSpaceFrustumCorner(farBottom, rightVector, m_farWidth);
	points[3] = calculateLightSpaceFrustumCorner(farBottom, leftVector, m_farWidth);
	points[4] = calculateLightSpaceFrustumCorner(nearTop, rightVector, m_nearWidth);
	points[5] = calculateLightSpaceFrustumCorner(nearTop, leftVector, m_nearWidth);
	points[6] = calculateLightSpaceFrustumCorner(nearBottom, rightVector, m_nearWidth);
	points[7] = calculateLightSpaceFrustumCorner(nearBottom, leftVector, m_nearWidth);
	return points;
}

glm::vec3 ShadowBox::calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width) {
	glm::vec3 point = startPoint +
		glm::vec3(direction.x * width, direction.y * width, direction.z * width);
	glm::vec4 point4f = glm::vec4(point.x, point.y, point.z, 1.f);
	return m_lightViewMatrix * point4f;
}
glm::mat4 ShadowBox::calculateCameraRotationMatrix() {
	glm::mat4 rotation;
	rotation = glm::rotate(-m_camera.getYaw(), glm::vec3(0, 1, 0)) * glm::rotate(-m_camera.getPitch(), glm::vec3(1,0,0));
	return rotation;
}
void ShadowBox::calculateWidthAndHeight() {
	m_farWidth = (float)(m_shadowDistance * glm::tan(glm::radians(45.f)));  //Math.tan(Math.toRadians(MasterRenderer.FOV)));
	m_nearWidth = (float)(0.1f
		* glm::tan(glm::radians(45.f)));
	m_farHeight = m_farWidth / getAspectRatio();
	m_nearHeight = m_nearWidth / getAspectRatio();
}
float ShadowBox::getAspectRatio() {
	return m_screenWidth / m_screenHeight;
}