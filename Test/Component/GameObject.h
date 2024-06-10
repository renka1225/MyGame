#pragma once
#include <list>
#include <string>

class GameObject
{
public:
	template <typename T>
	void AddComponent();
	void GetComponent();
	void DelComponent();
	void ShowComponents();

private:
	std::list<GameObject> list;
	//std::string objName = nullptr;
};

template<typename T>
inline void GameObject::AddComponent()
{
	list.push_back(std::make_shared<T>(list));
}
