#pragma once
class Player
{
public:
Player() : m_health(10), m_ammo(3){}
virtual void update();

private:
	uint32_t m_health;
	uint32_t m_ammo;
	
};

