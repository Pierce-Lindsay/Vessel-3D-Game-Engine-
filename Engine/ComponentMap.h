#pragma once
#include <vector>
#include <unordered_map>
#include <optional>
#include <algorithm>
#include <functional>
#include <memory>
#include "components/Component.h"
#include <typeindex>

namespace ve {

	/// <summary>
	/// A class that handles a hybrid unordered map and vector for mapping components. With key mapping in map mapped 
	/// to correcponding index in the vector which contains the value. This is for contiguous
	/// iteration aswell as fast access.
	/// </summary>
	/// <typeparam name="KEY"></typeparam>
	/// <typeparam name="VALUE"></typeparam>
	class ComponentMap
	{
	private:
		std::vector<std::unique_ptr<Component>> values; //index to values vector for fast contiguous update
		std::vector<std::type_index> keys; //index to keys vector for fast deletion and reverse lookup
		std::unordered_map <std::type_index, size_t> map;

	public:
		/// <summary>
		/// Adds the key to the vectormap or overrides the value
		/// if the key was already in the map.
		/// </summary>
		void add(std::type_index key, std::unique_ptr<Component> value);

		/// <summary>
		/// Retrieves the value associated with a given key, if it exists.
		/// </summary>
		/// <param name="key">The key to look up in the map.</param>
		/// <returns>An optional containing the value associated with the key if found; otherwise, std::nullopt.</returns>
		Component* get(std::type_index key);

		/// <summary>
		/// Determines whether the vectormap conatins the given key.
		/// </summary>
		/// <param name="key"></param>
		/// <returns>True if present, false else.</returns>
		bool contains(std::type_index key);

		/// <summary>
		/// Determines whether the vectormap conatins the given value.
		/// </summary>
		/// <returns>True if present, false else.</returns>
		//bool contains(VALUE value)
		//{
		//
		//}

		/// <summary>
		/// Removes the element associated with the specified key.
		/// Does not preserve order of the map.
		/// </summary>
		/// <param name="key">The key of the element to remove.</param>
		/// <returns>-1 for a removal fail, 0 else.</returns>
		int remove(std::type_index key);

		/// <summary>
		/// A map function that specifically is applied to every value
		/// in the VectorMap but returns void for each call on a value.
		/// </summary>
		void mapVoid(std::function <void(Component*)> func);
	};
}
