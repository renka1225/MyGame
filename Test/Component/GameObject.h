#pragma once
#include <list>
#include "Component.h"

class GameObject
{
public:
    template <typename T>
    void AddComponent()
    {
		list.push_back(std::make_shared<T>());
    }

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (auto& component : components)
		{
			if (item.GetType() == typeof(T))
			{
				obj = static_cast<T>(item);
			}
		}
		return obj;
	}

	template <typename T>
	void DelComponent()
	{
		for (auto& component : components)
		{
			if (item.GetType() == typeof(T))
			{
				obj = static_cast<T>(item);
			}
		}
		list.remove(obj);
	}

	template <typename T>
	void ShowComponents()
	{
		for (auto& component : components)
		{
			component->ShowComponentName();
		}
	}

private:
	std::list<std::shared_ptr<Component>> list;
	std::string objName = nullptr;
};
