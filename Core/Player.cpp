#include "SocketWrapperPCH.hpp"

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

void Player::WriteBits(OutputMemoryBitStream& outBitStream) const
{
	outBitStream.WriteBits(m_health, 7);
	outBitStream.WriteBits(m_ammo, 9);
	uint8_t nameLength = static_cast<uint8_t>(strlen(m_name));
	outBitStream.WriteBits(nameLength, 8);
	outBitStream.WriteBits(m_name, (nameLength * 8));
	outBitStream.Write(m_weapons);
	outBitStream.WritePos(m_position);
	outBitStream.Write(m_rotation);
}

void Player::ReadBits(InputMemoryBitStream& inBitStream)
{
	inBitStream.ReadBits(&m_health, 7);
	inBitStream.ReadBits(&m_ammo, 9);
	uint8_t nameLength;
	inBitStream.Read(nameLength);
	inBitStream.ReadBits(&m_name, (nameLength * 8));
	inBitStream.Read(m_weapons);
	inBitStream.ReadPos(m_position);
	inBitStream.Read(m_rotation);
}

void Player::toString() const
{
	std::cout << m_name << " has Health: " << m_health << ", Ammo: " << m_ammo <<
		" Position: " << "(" << m_position.mX << "," <<
		m_position.mY << "," << m_position.mZ << ")" << " Quaternion: " <<
		"(" << m_rotation.mX << "," << m_rotation.mY << "," << m_rotation.mZ << "," << m_rotation.mW << ")" << std::endl;
	for (const int m_weapon : m_weapons)
	{
		std::cout << m_weapon << std::endl;
	}
}
