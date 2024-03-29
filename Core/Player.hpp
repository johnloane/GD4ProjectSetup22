#pragma once
class Player : public GameObject
{
public:
	Player() : m_health(10), m_ammo(3), m_name("Default"), m_position(10, 10, 10), m_rotation(0, 0, 0, 1), m_weapons{ 60, 70, 80, 90, 100 }{}
	uint32_t GetHealth() const;
	uint32_t GetAmmo() const;
	void Write(OutputMemoryStream& out_stream) const;
	void Read(InputMemoryStream& in_stream);
	void WriteBits(OutputMemoryBitStream& outBitStream) const;
	void ReadBits(InputMemoryBitStream& instream);
	virtual void toString() const;


private:
	uint32_t m_health;
	uint32_t m_ammo;
	char m_name[128];
	Vector3 m_position;
	Quaternion m_rotation;
	vector<int> m_weapons;
	
};

