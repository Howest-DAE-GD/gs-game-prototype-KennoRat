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
	m_DashCounter = 0.f;
	m_SacrificeAvailable = false;
	m_IsDead = false;
	m_IsDashing = false;
}

void Player::Draw() const
{
	SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.f });
	FillRect(m_Player);

	if(m_IsDashing)
	{
		for(Point2f Points : m_DashPoints)
		{
			SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
			utils::DrawPoint(Points, 6.f);
		}
	}
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

		float TemporaryBoost{};
		if (m_IsDashing)
		{
			TemporaryBoost = 500.f;
			m_DashPoints.push_back(Point2f(m_Position.x + m_Width/2.f, m_Position.y + m_Width / 2.f));
			DashCounter(elapsedSec);
		}

		if (isUp)	m_Position.y -= (m_Speed + TemporaryBoost) * elapsedSec;
		if (isLeft) m_Position.x -= (m_Speed + TemporaryBoost) * elapsedSec;
		if (isRight)m_Position.x += (m_Speed + TemporaryBoost) * elapsedSec;
		if (isDown) m_Position.y += (m_Speed + TemporaryBoost) * elapsedSec;

		m_Player = Rectf{ m_Position.x, m_Position.y, m_Width, m_Width };

		if (m_SacrificeAvailable == false)
		{
			m_SacrificeCultMemberDelayCounter += elapsedSec;
			SacrificeCultMemberTimer();
		}

		float Top{ 860.f };
		float Bottom{ -160.f };
		float Left{ -300.f };
		float Right{ 1560.f };

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

void Player::SetIsDashing(bool IsDashing)
{
	m_IsDashing = IsDashing;
}

bool Player::GetIsDead()
{
	return m_IsDead;
}

bool Player::GetSacrificeAvailable()
{
	return m_SacrificeAvailable;
}

bool Player::GetIsDashing() const
{
	return m_IsDashing;
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

void Player::DashCounter(float elapsedSec)
{
	m_DashCounter += elapsedSec;
	if(m_DashCounter >= m_DASH_MAX)
	{
		std::cout << "Dash Stop" << std::endl;
		m_IsDashing = false;
		m_DashCounter -= m_DASH_MAX;
		m_DashPoints.clear();
	}
}
