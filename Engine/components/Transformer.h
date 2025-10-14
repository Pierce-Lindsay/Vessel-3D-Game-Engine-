#pragma once
#include "../external/glm/gtx/norm.hpp"
#include "Component.h"

namespace ve {

	/// <summary>
	/// Component for handling the transformation of an object. Transformation is
	/// described by a 3d position, 3 dimensions of scale, a rotation value in degrees
	/// and a 3d rotation axis.
	/// </summary>
	class Transformer : public Component
	{
	private:
		glm::vec3 pos = { 0.0, 0.0, 0.0 };
		float rotation = { 0 };
		glm::vec3 totalRotationAxis = { 0, 0, 1 };
		glm::vec3 previousUsedRotationAxis = { 0, 0, 1 };
		glm::vec3 dialation = { 1.0, 1.0, 1.0 };
		glm::mat4 modelMat = glm::mat4(1.0f);
		glm::mat4 rotationMat = glm::mat4(1.0f);
		bool changedTransform = false;
		//rotation is weird, we can't recalculate matrix from scratch every time
		bool rotationChanged = false; 

		/// <summary>
		/// Update the model matrix to account for the current position/dialation/rotation.
		/// </summary>
		void updateModelMat();

		/// <summary>
		/// Update the cached values for the rotation matrix by grabbing the quanternion
		/// and extracting the pertinent values.
		/// </summary>
		void updateCachedRotationValues();

	public:
		/// <summary>
		/// Create a transformer at 0, 0, 0 with unit scale and 0 rotation. 
		/// Has a default rotation axis of 0, 0, 1.
		/// </summary>
		Transformer();

		/// <summary>
		/// Create a transformer at the given position, scale, rotation, and rotation axis.
		/// </summary>
		Transformer(const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec3& rotationAxis);

		/// <summary>
		/// Create a transformer at the given position with unit scale and 0 rotation. 
		/// Has a default rotation axis of 0, 0, 1.
		/// </summary>
		Transformer(const glm::vec3& pos);


		/// <summary>
		/// Increment the rotation of the the transformer. Applies a rotation matrix
		/// with the specified axis and rotation value in degrees to the current
		/// rotation matrix using quanternions.
		/// </summary>
		void rotate(float rot, const glm::vec3& axis);

		/// <summary>
		/// Increment the rotation of the the transformer. Applies a rotation matrix
		/// with the previously used rotation axis and rotation value 
		/// in degrees to the current rotation matrix using quanternions.
		/// </summary>
		void rotate(float rot);

		/// <summary>
		/// Set the rotation matrix of the transformer with the
		/// given rotation in degrees and the given axis.
		/// </summary>
		void setRotation(float rotTotal, const glm::vec3& axis);

		/// <summary>
		/// Set the position of the transformer to the provided
		/// 3d world position.
		/// </summary>
		/// <param name="newPos"></param>
		void setPos(const glm::vec3& newPos);

		/// <summary>
		/// Move the position in 3d world space by the given
		/// delta.
		/// </summary>
		void move(const glm::vec3& delta);

		/// <summary>
		/// Set the scale of the transformer according to the vec3.
		/// </summary>
		void setScale(const glm::vec3& scale);

		/// <summary>
		/// Change the current scale of the transformer by adding the 
		/// provided delta to the current scale. Note, the scale value
		/// is not bounded by 0.
		/// </summary>
		void changeScaleByDelta(const glm::vec3& delta);

		/// <summary>
		/// Change the current scale of the transformer by multiplying
		/// the current values element-wise with the provided vec3 factor.
		/// Note, the input and result values are not bounded by 0.
		/// </summary>
		void changeScaleByFactor(const glm::vec3& factor);

		/// <summary>
		/// Change the current scale of the transformer by multiplying
		/// the current values by the provided factor.
		/// Note, the input and result values are not bounded by 0.
		/// </summary>
		void changeScaleUniform(float uniform);

		/// <summary>
		/// Set the current scale of the transformer by setting
		/// the current values of the scale to all be by the provided value.
		/// Note, the input and result values are not bounded by 0.
		/// </summary>
		void setScaleUniform(float value);

		/// <summary>
		/// Get the current position of the transformer.
		/// </summary>
		const glm::vec3& getPos() const;

		/// <summary>
		/// Get the current scale of the transformer.
		/// </summary>
		const glm::vec3& getScale() const;

		/// <summary>
		/// Get the current rotation desribed by the rotation matrices' quanternion in degrees.
		/// </summary>
		const float getRotation();

		/// <summary>
		/// Get the current rotation axis described by the rotation matrices' quanterion.
		/// </summary>
		const glm::vec3& getRotationAxis();

		/// <summary>
		/// Get the last used rotation axis to rotate the transformer.
		/// </summary>
		const glm::vec3& getPreviousUsedRotationAxis() const;

		/// <summary>
		/// Get the model matrix of the transformer.
		/// </summary>
		const glm::mat4& getModelMat();

		/// <summary>
		/// Get a unique pointer to deep copy of the transformer.
		/// Updates cached rotation values if neccessary.
		/// </summary>
		std::unique_ptr<Transformer> copy();

		/// <summary>
		/// Get whether this transformer has been updated. This indicates whether
		/// the next get the model matrix, the model matrix will need to be recalculated.
		/// </summary>
		bool getChangePending() const;

		/// <summary>
		/// Create a model matrix with the given position, scale, rotation, and rotation axis and
		/// return it.
		/// </summary>
		static glm::mat4 quickMakeModel(const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec3& rotationAxis);
	};

}
