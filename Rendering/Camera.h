#pragma once
#include "external/GLM/glm.hpp"

namespace ve
{
	/// <summary>
	/// Class representing a camera. The camera is responsible for 
	/// defining the view and projection matrices used for rendering.
	/// It can be configured for either perspective or orthographic projection.
	/// Default is orthographic projection with bounds of -1 to 1 in both x and y directions, 
	/// and a near plane of -1 and far plane of 1.
	/// </summary>
	class Camera
	{
	private:
		//view parameters
		glm::vec3 eye = glm::vec3(0, 0, 1);
		glm::vec3 at = glm::vec3(0, 0, 0);
		glm::vec3 up = glm::vec3(0, 1, 0);


		//projection parameters

		//perspective projection parameters
		float fov = 90.0f;	
		float aspectRatio = 1920.0f / 1080.0f;
		bool isPerspective = false;

		//orthographic projection parameters
		float lowerXBound = -1.0f;
		float upperXBound = 1.0f;
		float lowerYBound = -1.0f;
		float upperYBound = 1.0f;

		//both
		float nearPlane = -1;
		float farPlane = 1;

		bool editedView = true;

		void SetupLookAt();

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

	public:
		Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
		Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up, float fov, float aspectRatio, float nearPlane, float farPlane);
		Camera(float lowerXBound, float upperXBound, float lowerYBound, float upperYBound, float nearPlane, float farPlane);
		Camera();
		~Camera();

		void SetEye(const glm::vec3& eye);
		void SetAt(const glm::vec3& at);
		void SetUp(const glm::vec3& up);

		bool IsPerspective() const;
		void SetPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
		void SetOrthographicProjection(float lowerXBound, float upperXBound, float lowerYBound, float upperYBound, float nearPlane, float farPlane);

		float GetFOV() const;
		float GetAspectRatio() const;

		float GetNearPlane() const;
		float GetFarPlane() const;

		float GetLowerXBound() const;
		float GetUpperXBound() const;
		float GetLowerYBound() const;
		float GetUpperYBound() const;

		const glm::vec3& GetEye() const;
		const glm::vec3& GetAt() const;
		const glm::vec3& GetUp() const;

		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetProjectionMatrix() const;	
	};
}