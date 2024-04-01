#include "Entity.h"
#include "Component.h"
#include "Message.h"

void Entity::Slot(double _TickRate)
{
	for (int i = 0; i < m_Components.size(); ++i)
	{
		m_Components[i]->Slot(_TickRate);
	}
}

void Entity::SendMessage(Message* _msg)
{
	for (int i = 0; i < m_Components.size(); ++i)
	{
		m_Components[i]->ReceiveMessage(_msg);
	}
}

Entity::~Entity()
{
	for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		delete *it;
	}
}
