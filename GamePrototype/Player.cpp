#include "pch.h"
#include "Player.h"

Player::Player(Point2f position, float width) :m_Position{ position }, m_Width{width}
{
	m_Direction = DirectionPlayer::Down;
	m_Speed = 300.f;
	m_Player = Rectf{m_Position.x, m_Position.y, m_Width, m_Width};
	m_CultMembers = -1;
	m_TotalCultMembers = -1;
	m_SacrificeCultMemberDelayCounter = 0.f;
	m_SacrificeAvailable = false;
	m_IsDead = false;
}

void Player::Draw() const
{
	SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.f });
	FillRect(m_Player);

}

void Player::Update(float elapsedSec, bool IsLeft, bool IsDown, bool IsRight , bool IsUp )
{

	if(m_IsDead == false)
	{
		// Check the keys
		const bool isUp{ IsUp };
		const bool isDown{ IsDown };
		const bool isLeft{ IsLeft };
		const bool isRight{ IsRight };

		// update direction
		if (isUp) {
			if (isLeft)			m_Direction = DirectionPlayer::UpLeft;
			else if (isRight)	m_Direction = DirectionPlayer::UpRight;
			else				m_Direction = DirectionPlayer::Up;
		}
		else if (isDown) {
			if (isLeft)			m_Direction = DirectionPlayer::DownLeft;
			else if (isRight)	m_Direction = DirectionPlayer::DownRight;
			else				m_Direction = DirectionPlayer::Down;
		}
		else if (isLeft)		m_Direction = DirectionPlayer::Left;
		else if (isRight)		m_Direction = DirectionPlayer::Right;

		// update position

		if (isUp)	m_Position.y -= m_Speed * elapsedSec;
		if (isLeft) m_Position.x -= m_Speed * elapsedSec;
		if (isRight)m_Position.x += m_Speed * elapsedSec;
		if (isDown) m_Position.y += m_Speed * elapsedSec;

		m_Player = Rectf{ m_Position.x, m_Position.y, m_Width, m_Width };

		if (m_SacrificeAvailable == false)
		{
			m_SacrificeCultMemberDelayCounter += elapsedSec;
			SacrificeCultMemberTimer();
		}

		float Top{ 700.f };
		float Bottom{ -3.f };
		float Left{ 0.f };
		float Right{ 1250.f };

		if (m_Position.y <= Bottom)
		{
			m_Position.y = Bottom;
		}
		else if (m_Position.y >= Top)
		{
			m_Position.y = Top;
		}

		if (m_Position.x >= Right)
		{
			m_Position.x = Right;
		}
		else if (m_Position.x <= Left)
		{
			m_Position.x = Left;
		}
	}
}

void Player::IncrementCultMembers()
{
	++m_TotalCultMembers;
	++m_CultMembers;
}

void Player::DecrementCultMembers()
{
	--m_CultMembers;
}

void Player::SacrificeCultMemberTimer()
{
	if(m_SacrificeCultMemberDelayCounter >= m_SACRIFICE_CULT_MAX)
	{
		m_SacrificeAvailable = true;
		m_SacrificeCultMemberDelayCounter -= m_SACRIFICE_CULT_MAX;
		std::cout << "Sacrifice is available" << std::endl;
	}
}

void Player::PlusSpeed()
{
	m_Speed += 100.f;
}

void Player::SetSacrificeAvailable(bool Sacrifice)
{
	m_SacrificeAvailable = Sacrifice;
}

void Player::SetIsDead(bool IsDead)
{
	m_IsDead = IsDead;
}

bool Player::GetIsDead()
{
	return m_IsDead;
}

bool Player::GetSacrificeAvailable()
{
	return m_SacrificeAvailable;
}

int Player::GetTotalCultMembers()
{
	return m_TotalCultMembers;
}

int Player::GetCultMembers()
{
	return m_CultMembers;
}

Point2f Player::GetPosition() const
{
	return Point2f{ m_Position.x + m_Width / 2.f, m_Position.y + m_Width / 2.f };
}

Rectf Player::GetHitbox() const
{
	return m_Player;
}
