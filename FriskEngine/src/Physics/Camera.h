#pragma once

#include <memory>

namespace Frisk
{
    namespace Input
    {
        class InputManager;
    }

	class Camera
	{

	public:
		Camera(const VEC3& position, const VEC3& target, const float aspect_ratio, const VEC3& fov_near_far);
		~Camera() = default;

		MAT4 getView() const;
		MAT4 getProj() const;

		void movePos(float speed, const VEC3& direction);
		void moveDir(float d_yaw, float d_pitch);

		void cameraUpdate(double dt, const std::unique_ptr<Input::InputManager>& inputManager);

		VEC3 getPos() const
	    {
			return m_CameraPosition;
		}
		VEC3 getFront() const
		{
			return m_CameraFront;
		}
		VEC3 getRight() const
		{
			return m_CameraRight;
		}

		float getYaw() const
		{
			return m_CameraYaw;
		}
		float getPitch() const
		{
			return m_CameraPitch;
		}

		void setRestricted(bool state)
		{
		    m_Restricted = state;
		}

	private:
		VEC3 m_CameraPosition = VEC3(0.0f);

		VEC3 m_CameraFront = VEC3(0.0f);
		VEC3 m_CameraRight = VEC3(0.0f);
		VEC3 m_CameraUp = VEC3(0.0f);

		float m_CameraYaw = -90.0f;
		float m_CameraPitch = 0.0f;

		float m_AspectRatio = 16.0f / 9.0f;

		float m_FOV = 45.0f;
		float m_NearPlane = 0.1f;
		float m_FarPlane = 100.0f;

		float m_CamSpeed = 5.0f;
		float m_CamSens = 0.2f;

		bool m_Restricted = false;

	};
}
