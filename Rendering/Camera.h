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

		/// <summary>
		/// Create a camera with the given view parameters and default orthographic projection parameters.
		/// Default projection parameters are bounds of -1 to 1 in both x and y directions, and a near plane of -1 and far plane of 1.
		/// </summary>
		Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);

		/// <summary>
		/// Create a camera with the given view parameters and perspective projection parameters.
		/// </summary>
		Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up, float fov, float aspectRatio, float nearPlane, float farPlane);

		/// <summary>
		/// Create orthographic camera with the given orthographic projection parameters. And default view parameters.
		/// Default view parameters are eye at (0, 0, 1), at at (0, 0, 0) and up as (0, 1, 0).
		/// </summary>
		Camera(float lowerXBound, float upperXBound, float lowerYBound, float upperYBound, float nearPlane, float farPlane);

		/// <summary>
		/// Create an orthographic camera with default view parameters and orthographic projection parameters.
		/// Default projection parameters are bounds of -1 to 1 in both x and y directions, and a near plane of -1 and far plane of 1.
		/// Default view parameters are eye at (0, 0, 1), at at (0, 0, 0) and up as (0, 1, 0).
		/// </summary>
		Camera();
		~Camera();

		/// <summary>
		/// Set the eye position of the camera. This will mark the view matrix as edited, and it will be recalculated when requested.
		/// </summary>
		void SetEye(const glm::vec3& eye);

		/// <summary>
		/// Set the at position of the camera. This will mark the view matrix as edited, and it will be recalculated when requested.
		/// </summary>
		void SetAt(const glm::vec3& at);

		/// <summary>
		/// Set the up vector of the camera. This will mark the view matrix as edited, and it will be recalculated when requested.
		/// </summary>
		/// <param name="up"></param>
		void SetUp(const glm::vec3& up);

		/// <summary>
		/// Get whether the camera is using perspective projection. 
		/// This is determined by whether the last projection set was perspective or orthographic.
		/// </summary>
		bool IsPerspective() const;

		/// <summary>
		/// Set the camera to be a perspective projection with the given parameters.
		/// </summary>
		void SetPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

		/// <summary>
		/// Set the camera to be an orthographic projection with the given parameters.
		/// </summary>
		void SetOrthographicProjection(float lowerXBound, float upperXBound, float lowerYBound, float upperYBound, float nearPlane, float farPlane);

		/// <summary>
		/// Get the field of view of the camera. 
		/// This is only meaningful if the camera is in perspective mode. 
		/// If the camera is in orthographic mode, a warning will be 
		/// logged and the value returned may not be meaningful. 
		/// </summary>
		float GetFOV() const;

		/// <summary>
		/// Get the aspect ratio of the camera. 
		/// This is only meaningful if the camera is in perspective mode. 
		/// If the camera is in orthographic mode, a warning will be 
		/// logged and the value returned may not be meaningful. 
		/// </summary>
		float GetAspectRatio() const;

		/// <summary>
		/// Get the near plane of the camera. 
		/// </summary>
		float GetNearPlane() const;

		/// <summary>
		/// Get the far plane of the camera.
		/// </summary>
		float GetFarPlane() const;

		/// <summary>
		/// Get leftward bounds of an orthographic camera.
		/// </summary>
		float GetLowerXBound() const;

		/// <summary>
		/// Get rightward bounds of an orthographic camera.
		/// </summary>
		float GetUpperXBound() const;

		/// <summary>
		/// Get bottom bounds of an orthographic camera.
		/// </summary>
		float GetLowerYBound() const;

		/// <summary>
		/// Get upper bounds of an orthographic camera.
		/// </summary>
		float GetUpperYBound() const;

		/// <summary>
		/// Get the eye position of the camera.
		/// </summary>
		const glm::vec3& GetEye() const;

		/// <summary>
		/// Get the at position of the camera.
		/// </summary>
		const glm::vec3& GetAt() const;

		/// <summary>
		/// Get the up vector of the camera.
		/// </summary>
		const glm::vec3& GetUp() const;

		/// <summary>
		/// Get the view matrix of the camera. 
		/// If the view parameters have been edited 
		/// since the last time the view matrix was calculated, 
		/// it will be recalculated before being returned.
		/// </summary>
		const glm::mat4& GetViewMatrix() const;

		/// <summary>
		/// Get the projection matrix of the camera.
		/// </summary>
		const glm::mat4& GetProjectionMatrix() const;	
	};
}