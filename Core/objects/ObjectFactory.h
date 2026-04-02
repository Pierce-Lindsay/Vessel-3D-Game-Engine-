#pragma once
#include "../scenes/scene.h"
#include "../components/Transformer.h"
#include "Object.h"

namespace ve {

	/// <summary>
	/// Create an object with the given type name and automatically
	/// add it to the provided scene. If scene is null, returns null.
	/// </summary>
	Object* createSceneObject(const std::string& type_name, Scene* scene);

	/// <summary>
	/// Create an object with a transformer component the given type name and position; automatically
	/// add it to the provided scene. If scene is null, returns null.
	/// </summary>
	Object* createSceneTransformerObject(const std::string& type_name, const glm::vec3& pos, Scene* scene);

	/// <summary>
	/// Create an object with a transformer component and null/empty hierarchy, the given type name and position; automatically
	/// add it to the provided scene. If scene is null, returns null.
	/// </summary>
	Object* createSceneTransformerHierarchyObject(const std::string& type_name, const glm::vec3& pos, Scene* scene);
}