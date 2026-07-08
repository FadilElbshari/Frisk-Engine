#include "Physics/Camera.h"
#include "Engine/Core/Log.h"
#include "InputManager/InputManager.h"
#include "glm/ext/quaternion_geometric.hpp"

namespace Frisk
{

	Camera::Camera(const VEC3& position, const VEC3& target, const float aspect_ratio, const VEC3& fov_near_far) :
        m_CameraPosition(position),
        m_CameraFront(glm::normalize(target - position)),

        m_CameraPitch(glm::degrees(std::asin(m_CameraFront.y))),
		m_CameraYaw(glm::degrees(std::atan2(m_CameraFront.z, m_CameraFront.x))),

		m_AspectRatio(aspect_ratio),
		m_FOV(fov_near_far.x),
		m_NearPlane(fov_near_far.y),
		m_FarPlane(fov_near_far.z)
	{
		const VEC3 worldUp = VEC3(0.0f, 1.0f, 0.0f);

		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, worldUp));
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
	}

	MAT4 Camera::getView() const
	{
		return glm::lookAt(
			m_CameraPosition,
			m_CameraPosition + m_CameraFront,
			m_CameraUp
		);
	}

	MAT4 Camera::getProj() const
	{
		MAT4 proj = MAT4(1.0f);
		proj = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
		return proj;
	}

	void Camera::movePos(float speed, const VEC3& direction)
	{

		VEC3 resulting_pos = m_CameraPosition + speed * direction;

		if (!m_Restricted)
		{
			m_CameraPosition = resulting_pos;
			return;
		}

	}

	void Camera::moveDir(float d_yaw, float d_pitch)
	{
		m_CameraYaw += d_yaw;
		m_CameraPitch += d_pitch;

		if (m_CameraPitch > 89.0f)
			m_CameraPitch = 89.0f;
		if (m_CameraPitch < -89.0f)
			m_CameraPitch = -89.0f;

		VEC3 dir(0.0f);
		dir.x = cos(glm::radians(m_CameraYaw)) * cos(glm::radians(m_CameraPitch));
		dir.y = sin(glm::radians(m_CameraPitch));
		dir.z = sin(glm::radians(m_CameraYaw)) * cos(glm::radians(m_CameraPitch));

		m_CameraFront = glm::normalize(dir);

		const VEC3 worldUp = VEC3(0.0f, 1.0f, 0.0f);

		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, worldUp));
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
	}

	void Camera::cameraUpdate(double dt, const std::unique_ptr<Input::InputManager>& inputManager)
	{

		const float cam_speed = m_CamSpeed * dt;
		auto dirVector = VEC3(0.0f);


		// Ensure char doesnt fly when pointing upwards by neglecting the y component of the front vecotr
		auto forwardDir = getFront();
		forwardDir.y = 0;

		if (glm::length(forwardDir) > 0) forwardDir = glm::normalize(forwardDir);

		if (inputManager->GetKeyStatus(GLFW_KEY_W) == Input::KeyStatus::Pressed) dirVector += forwardDir;
		if (inputManager->GetKeyStatus(GLFW_KEY_S) == Input::KeyStatus::Pressed) dirVector -= forwardDir;
		if (inputManager->GetKeyStatus(GLFW_KEY_A) == Input::KeyStatus::Pressed) dirVector -= getRight();
		if (inputManager->GetKeyStatus(GLFW_KEY_D) == Input::KeyStatus::Pressed) dirVector += getRight();

		dirVector = glm::normalize(dirVector);
		if (glm::length(dirVector) > 0)
		{
		    movePos(cam_speed, dirVector);
		}

		double xoffset;
		double yoffset;

		inputManager->getMousePosDelta(xoffset, yoffset);

		xoffset *= m_CamSens;
		yoffset *= m_CamSens;

		moveDir((float)xoffset, (float)yoffset);

	}
}
