#pragma once
#include <vector>

class Component;
class Message;

class Entity
{
protected:
	std::vector<Component*> m_Components;

public:
	/* Add a Component of type T */
	template <class T>
	void AddComponent(T* _Component);

	/* Find Component of type T */
	template<class T>
	T* FindComponent();

	/* Call Slot for each Component */
	void Slot(double _TickRate);

	/* Send Message to all Components */
	void SendMessage(Message* _msg);

	virtual ~Entity();
};

template<class T>
inline void Entity::AddComponent(T* _Component)
{
	m_Components.push_back(_Component);
}

template<class T>
inline T* Entity::FindComponent()
{
	// Improve performance
	int idx = 0;
	int size = m_Components.size();

	while (idx < size)
	{
		if (T* foundComponent = dynamic_cast<T*>(m_Components[idx]))
		{
			return foundComponent;
		}
		++idx;
	}
	return nullptr;
}