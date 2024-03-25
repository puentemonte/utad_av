#pragma once
#include <vector>

class Component;

class Entity
{
public:
	void AddComponent(Component* _component);

	Component* FindComponent();
	void Slot();

protected:
		std::vector<Component*> m_Components;
};

