#include "transformer.h"

using namespace ve;

Transformer::Transformer()
{
	setType("transformer");
	updateModelMat();
}

Transformer::Transformer(const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec3& rotationAxis) :
	pos{ pos }, dialation{ scale }, rotation{ rotation }, totalRotationAxis{ rotationAxis }, previousUsedRotationAxis{rotationAxis}
{
	setRotation(rotation, rotationAxis); //update rotation matrix before
	setType("transformer");
	updateModelMat();
}

Transformer::Transformer(const glm::vec3& pos) : pos{ pos }
{
	setType("transformer");
	updateModelMat();
}

void Transformer::updateModelMat()
{
	//reverse order as required to work with glm
	//only multiply required matrixes, matrix multiplication is slow!!!!
	modelMat = glm::mat4(1.0f);

	if (glm::length2(pos) != 0.0)
		modelMat = glm::translate(modelMat, pos);

	if (getRotation() != 0.0) //should be correct, might need to swap * order, though
		modelMat = modelMat * rotationMat;

	if (!(dialation.x == 1.0 && dialation.y == 1.0 && dialation.z == 1.0))
		modelMat = glm::scale(modelMat, dialation);
	//reset chnage check
	changedTransform = false;
}

const glm::mat4& Transformer::getModelMat()
{
	//only recalculate is something changed
	if (changedTransform)
		updateModelMat();

	return modelMat;
}


void Transformer::rotate(float rot, const glm::vec3& axis)
{
	if (rot != 0.0)
	{
		previousUsedRotationAxis = axis;
		changedTransform = true;
		rotationChanged = true;
		rotationMat = glm::rotate(rotationMat, glm::radians(rot), axis);
	}
}

void Transformer::rotate(float rot)
{
	if (rot != 0)
	{
		changedTransform = true;
		rotationChanged = true;
		rotationMat = glm::rotate(rotationMat, glm::radians(rot), previousUsedRotationAxis);
	}
}

void Transformer::setRotation(float rotTotal, const glm::vec3& axis)
{
	changedTransform = true;
	rotationChanged = true;
	previousUsedRotationAxis = axis;
	rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotTotal), axis);
}

void Transformer::setPos(const glm::vec3& newPos)
{
	if (pos != newPos)
	{
		changedTransform = true;
		pos = newPos;
	}
}

void Transformer::move(const glm::vec3& delta)
{
	//length 2 computes no sqrt but we dont care abt that
	if (glm::length2(delta) != 0)
	{
		changedTransform = true;
		pos += delta;
	}

}

void Transformer::setScale(const glm::vec3& scale)
{
	if (dialation != scale)
	{
		changedTransform = true;
		dialation = scale;
	}

}

void Transformer::changeScaleByDelta(const glm::vec3& delta)
{
	if (glm::length2(delta) != 0)
	{
		changedTransform = true;
		dialation += delta;
	}
}

void Transformer::changeScaleByFactor(const glm::vec3& factor)
{
	//doing these condistionals is always faster than our matrix multiplications
	if (!(factor.x == 1.0 && factor.y == 1.0 && factor.z == 1.0))
	{
		changedTransform = true;
		dialation.x *= factor.x;
		dialation.y *= factor.y;
		dialation.z *= factor.z;
	}
}

void Transformer::changeScaleUniform(float uniform)
{
	//doing these condistionals is always faster than our matrix multiplications
	if (uniform != 1.0)
	{
		changedTransform = true;
		dialation *= uniform;
	}
}

void Transformer::setScaleUniform(float value)
{
	//doing these condistionals is always faster than our matrix multiplications
	if (dialation.x != value || dialation.y != value || dialation.z != value)
	{
		changedTransform = true;
		dialation = { value, value, value };
	}
}


const glm::vec3& Transformer::getPos() const
{
	return pos;
}

const glm::vec3& Transformer::getScale() const
{
	return dialation;
}

const float Transformer::getRotation()
{
	if (rotationChanged)//changed so cache new current rotation values
	{
		updateCachedRotationValues();
		rotationChanged = false;
	}
	return rotation;
}

const glm::vec3& Transformer::getRotationAxis()
{
	if (rotationChanged)//changed so cache new current rotation values
	{
		updateCachedRotationValues();
		rotationChanged = false;
	}
	return totalRotationAxis;
}

const glm::vec3& Transformer::getPreviousUsedRotationAxis() const
{
	return previousUsedRotationAxis;
}

void Transformer::updateCachedRotationValues()
{
	glm::quat quanternion = glm::quat(rotationMat);
	rotation = glm::degrees(glm::angle(quanternion));
	totalRotationAxis = glm::axis(quanternion);
}


std::unique_ptr<Transformer> Transformer::copy()
{
	auto tPointer = std::make_unique<Transformer>(Transformer(pos, dialation, getRotation(), getRotationAxis()));
	return tPointer;
}

bool Transformer::getChangePending() const
{
	return changedTransform;
}


glm::mat4 Transformer::quickMakeModel(const glm::vec3& pos, const glm::vec3& scale, float rotation, const glm::vec3& rotationAxis)
{
	glm::mat4 modelMat = glm::mat4(1.0f);

	if (glm::length2(pos) != 0.0)
		modelMat = glm::translate(modelMat, pos);

	if (rotation != 0.0)
		modelMat = glm::rotate(modelMat, glm::radians(rotation), rotationAxis);

	if (!(scale.x == 1.0 && scale.y == 1.0 && scale.z == 1.0))
		modelMat = glm::scale(modelMat, scale);

	return modelMat;
}

