#include "Camera.h"
#include "Instrumentation/logging/LogManager.h"
#include <external/glm/gtc/matrix_transform.hpp>

namespace ve
{
	Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
		:eye{eye}, at{at}, up{up}
	{
		SetupLookAt();
		SetOrthographicProjection(lowerXBound, upperXBound, lowerYBound, upperYBound, nearPlane, farPlane);
	}
	Camera::Camera()
	{
		SetupLookAt();
		SetOrthographicProjection(lowerXBound, upperXBound, lowerYBound, upperYBound, nearPlane, farPlane);
	}

	Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up, float fov, float aspectRatio, float nearPlane, float farPlane)
		: eye{ eye }, at{ at }, up{ up }, fov{ fov }, aspectRatio{ aspectRatio }, nearPlane{ nearPlane }, farPlane{ farPlane }, isPerspective{ true }
	{
		SetupLookAt();
		SetPerspectiveProjection(fov, aspectRatio, nearPlane, farPlane);
	}

	Camera::Camera(float lowerXBound, float upperXBound, float lowerYBound, float upperYBound, float nearPlane, float farPlane)
		: lowerXBound{ lowerXBound }, upperXBound{ upperXBound }, lowerYBound{ lowerYBound }, upperYBound{ upperYBound }, nearPlane{ nearPlane }, farPlane{ farPlane }, isPerspective{ false }
	{
		SetupLookAt();
		SetOrthographicProjection(lowerXBound, upperXBound, lowerYBound, upperYBound, nearPlane, farPlane);
	}

	Camera::~Camera()
	{

	}

	void Camera::SetEye(const glm::vec3& eye)
	{
		if (eye != this->eye)
		{
			this->eye = eye;
			editedView = true;
		}
	}
	void Camera::SetAt(const glm::vec3& at)
	{
		if (at != this->at)
		{
			this->at = at;
			editedView = true;
		}
	}
	void Camera::SetUp(const glm::vec3& up)
	{
		if (up != this->up)
		{
			this->up = up;
			editedView = true;
		}
	}

	const glm::vec3& Camera::GetEye() const
	{
		return eye;
	}
	const glm::vec3& Camera::GetAt() const
	{
		return at;
	}
	const glm::vec3& Camera::GetUp() const
	{
		return up;
	}

	const glm::mat4& Camera::GetViewMatrix() const
	{
		return viewMatrix;
	}
	const glm::mat4& Camera::GetProjectionMatrix() const
	{
		return projectionMatrix;
	}

	void Camera::SetupLookAt()
	{
		viewMatrix = glm::lookAt(eye, at, up);
		editedView = false;
	}

	void Camera::SetPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		this->fov = fov;
		this->aspectRatio = aspectRatio;
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;
		projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
	}

	void Camera::SetOrthographicProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		this->lowerXBound = left;
		this->upperXBound = right;
		this->lowerYBound = bottom;
		this->upperYBound = top;
		this->nearPlane = nearPlane;
		this->farPlane = farPlane;
		projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
	}

	float Camera::GetFOV() const
	{
		if(!isPerspective)
			VE_WARN("Camera is not in perspective mode. FOV is not meaningful.");

		return fov;
	}

	float Camera::GetAspectRatio() const
	{
		if(!isPerspective)
			VE_WARN("Camera is not in perspective mode. Aspect ratio is not meaningful.");

		return aspectRatio;
	}

	float Camera::GetNearPlane() const
	{
		return nearPlane;
	}

	float Camera::GetFarPlane() const
	{
		return farPlane;
	}

	float Camera::GetLowerXBound() const
	{
		if(isPerspective)
			VE_WARN("Camera is not in orthographic mode. X bounds are not meaningful.");

		return lowerXBound;
	}

	float Camera::GetUpperXBound() const
	{
		if (isPerspective)
			VE_WARN("Camera is not in orthographic mode. X bounds are not meaningful.");

		return upperXBound;
	}

	float Camera::GetLowerYBound() const
	{
		if (isPerspective)
			VE_WARN("Camera is not in orthographic mode. Y bounds are not meaningful.");

		return lowerYBound;
	}

	float Camera::GetUpperYBound() const
	{
		if(isPerspective)
			VE_WARN("Camera is not in orthographic mode. Y bounds are not meaningful.");

		return upperYBound;
	}

	bool Camera::IsPerspective() const
	{
		return isPerspective;
	}

}