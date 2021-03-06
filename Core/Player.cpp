#include "SocketWrapperPCH.hpp"
#include "Player.hpp"

uint32_t Player::GetHealth() const
{
	return m_health;
}

uint32_t Player::GetAmmo() const
{
	return m_ammo;
}

void Player::Write(OutputMemoryStream& out_stream) const
{
	out_stream.Write(m_health);
	out_stream.Write(m_ammo);
	out_stream.Write(m_name, 128);
	out_stream.Write(m_position);
	out_stream.Write(m_rotation);
	out_stream.Write(m_weapons);
}

void Player::Read(InputMemoryStream& in_stream)
{
	in_stream.Read(m_health);
	in_stream.Read(m_ammo);
	in_stream.Read(m_name, 128);
	in_stream.Read(m_position);
	in_stream.Read(m_rotation);
	in_stream.Read(m_weapons);
}

void Player::toString() const
{
	std::cout << m_name << " has Health: " << m_health << ", Ammo: " << m_ammo <<
		" Position: " << "(" << m_position.mX << "," <<
		m_position.mY << "," << m_position.mZ << ")" << " Quaternion: " <<
		"(" << m_rotation.mX << "," << m_rotation.mY << "," << m_rotation.mZ << "," << m_rotation.mW << ")" << std::endl;
	for (int i = 0; i < m_weapons.size(); i++)
	{
		std::cout << m_weapons[i] << std::endl;
	}
}
