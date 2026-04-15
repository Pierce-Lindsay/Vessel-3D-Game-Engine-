#pragma once
#include <vector>
#include <unordered_map>
#include <optional>
#include <algorithm>
#include <functional>
#include <memory>
#include <typeindex>


namespace ve {

	template <typename KEY, typename UNIQUE_PTR_VALUE>
	/// <summary>
	/// A hybrid unordered hashmap with a vector. Values in the array match to a the value type
	/// specified by the UNIQUE_PTR_VALUE type. This structure is meant for mapping a key value 
	/// to a std::unique_ptr value. When inititializing the class, specify the value type of the
	/// unqiue ptr as the templated value, for example std::unique_ptr<int>, specify int.
	/// Offers contiguous storage for fast iteration as well as aproximetly o(1) insertion and deletion.
	/// </summary>
	class VectorMap {
	private:
		std::vector<std::unique_ptr<UNIQUE_PTR_VALUE>> values; //index to values vector for fast contiguous update
		std::vector<KEY> keys; //index to keys vector for fast deletion and reverse lookup
		std::unordered_map <KEY, size_t> map;

	public:
		/// <summary>
		/// Add a new entry to the map or override the current entry with the given
		/// key. Return a normal raw pointer to the value.
		/// </summary>
		/// 
		VectorMap() = default;
		// Disable copying
		VectorMap(const VectorMap&) = delete;
		VectorMap& operator=(const VectorMap&) = delete;

		// Enable moving
		VectorMap(VectorMap&&) noexcept = default;
		VectorMap& operator=(VectorMap&&) noexcept = default;

		UNIQUE_PTR_VALUE* add(KEY key, std::unique_ptr<UNIQUE_PTR_VALUE> value)
		{
			UNIQUE_PTR_VALUE* value_ptr = value.get();
			if (map.contains(key))	//first  determine if already in
				values[map[key]] = std::move(value);
			else
			{
				values.push_back(std::move(value));
				keys.push_back(std::move(key));
				map[keys[keys.size() - 1]] = values.size() - 1;
			}
			return value_ptr;
		}

		/// <summary>
		/// Get a raw pointer to the key-specified entry in the map or return null if not found.
		/// </summary>
		UNIQUE_PTR_VALUE* get(KEY key) 
		{
			if (map.contains(key))//first  determine if already in
				return values[map[key]].get(); //return raw pointer if unique pointer
			return NULL;
		}

		/// <summary>
		/// Retrieve const reference to all keys in the map.
		/// </summary>
		const std::vector<KEY>& getKeys() const
		{
			return keys;
		}

		/// <summary>
		/// Retrieve const pointer to the vector of all values in the map.
		/// </summary>
		const std::vector<std::unique_ptr<UNIQUE_PTR_VALUE>>& getValues() const
		{
			return values;
		}

		/// <summary>
		/// Find if the key is defined in the map, return false if not found, true else.
		/// </summary> 
		bool contains(KEY key) const
		{
			return map.contains(key);
		}

		/// <summary>
		/// Remove the value and key with the specified key from the map. This operation does not
		/// preserve order and returns -1 on removal item not found, 0 else.
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		int remove(KEY key)
		{
			if (!map.contains(key))
				return -1;
			else
			{
				size_t index = map[key];
				size_t lastIndex = keys.size() - 1;
				if (values.size() != 1)
				{
					std::swap(keys[index], keys[lastIndex]);
					std::swap(values[index], values[lastIndex]);
					map[keys[index]] = index;
				}
				map.erase(keys[lastIndex]);
				keys.pop_back();
				values.pop_back();
				return 0;
			}
		}

		/// <summary>
		/// Remove the value and key with the specified key from the map and return a unique_ptr to the value. This operation does not
		/// preserve order and returns null if removal item was not found.
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::unique_ptr<UNIQUE_PTR_VALUE> swapOut(KEY key)
		{
			if (!map.contains(key))
				return nullptr;

			auto returnValue = std::move(values[map[key]]);
			remove(key); // already checks if key exists, no need to validate again
			return returnValue;
		}

		/// <summary>
		/// Remove all map elements.
		/// </summary>
		void clear()
		{
			values.clear();
			keys.clear();
			map.clear();
		}

		/// <summary>
		/// Apply the given map function to all values, the provided function ptr 
		/// takes in a raw pointer to the value unique_ptr type
		/// and returns void.
		/// </summary>
		void mapVoid(std::function <void(UNIQUE_PTR_VALUE*)> func)
		{
			for (int i = 0; i < values.size(); i++)
				func(values[i].get());
		}
	};
}