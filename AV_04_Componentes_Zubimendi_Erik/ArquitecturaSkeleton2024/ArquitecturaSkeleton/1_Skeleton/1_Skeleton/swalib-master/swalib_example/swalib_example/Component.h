#pragma once

class Entity;
class Message;

class Component
{
protected:
	Entity* m_Owner;

public:
	virtual void Slot(double _TickRate = 1.f / 60.f) = 0;
	virtual void ReceiveMessage(Message* _msg) = 0;
};