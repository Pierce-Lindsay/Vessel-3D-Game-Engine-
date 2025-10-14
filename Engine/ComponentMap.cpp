#include "ComponentMap.h"

using namespace ve;

void ComponentMap::add(std::type_index key, std::unique_ptr<Component> value)
{
	if (map.contains(key))	//first  determine if already in
		values[map[key]] = std::move(value);
	else
	{
		values.push_back(std::move(value));
		keys.push_back(std::move(key));
		map[keys[keys.size() - 1]] = values.size() - 1;
	}
}

Component* ComponentMap::get(std::type_index key)
{
	if (map.contains(key))//first  determine if already in
		return values[map[key]].get(); //return raw pointer if unique pointer
	return NULL;
}

bool ComponentMap::contains(std::type_index key)
{
	return map.contains(key);
}

/// <summary>
/// Determines whether the vectormap conatins the given value.
/// </summary>
/// <returns>True if present, false else.</returns>
//bool contains(VALUE value)
//{
//
//}

int ComponentMap::remove(std::type_index key)
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

void ComponentMap::mapVoid(std::function <void(Component*)> func)
{
	for (int i = 0; i < values.size(); i++)
		func(values[i].get());
}