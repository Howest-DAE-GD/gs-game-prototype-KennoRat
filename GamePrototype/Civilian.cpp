#include "pch.h"
#include "Civilian.h"

int Civilian::m_CultID{ -1 };

Civilian::Civilian(Point2f position, float width, bool IsCultMember): m_Position{position}, m_Width{width}, m_IsCultMember{ IsCultMember }
{
	m_DirectionPlayer = Player::DirectionPlayer::Up;
	m_Speed = 300.f;
	m_Person = Rectf{ m_Position.x, m_Position.y, m_Width, m_Width };
	m_IsMoving = false;
	m_IsDead = false;
	m_IsCultMember = false;
	m_DistanceRange = 4.f;
	m_NewPositionCounter = 0.f;
	
	++m_CultID;

	m_PersonalCultId = m_CultID;
}

void Civilian::Draw() const
{
	if(m_IsDead == false)
	{
		if (m_IsCultMember)
		{
			SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.f });
			DrawRect(m_Person);
		}
		else
		{
			SetColor(Color4f{ 0.4f, 0.4f, 1.0f, 1.f });
			FillRect(m_Person);
		}
	}
	else
	{
		SetColor(Color4f{ 0.4f, 1.0f, 4.0f, 1.f });
		FillRect(m_Person);
	}

}

void Civilian::Update(float elapsedSec, const Point2f& PlayerPosition, Player::DirectionPlayer PlayerDiretion)
{
	m_Person = Rectf{ m_Position.x, m_Position.y, m_Width, m_Width };

	m_PlayerPosition = PlayerPosition;
	m_DirectionPlayer = PlayerDiretion;

	if(m_IsCultMember){
		m_NewPosition = m_PlayerPosition;
	}

	m_NewPositionCounter += elapsedSec;

	if (m_IsDead == false)
	{
		if (m_IsMoving == false && m_IsCultMember == false)
		{
			m_NewPositionCounter += elapsedSec;
			MakeNewRandomPosition();
		}
		else
		{
			GoToRandomPosition(elapsedSec, PlayerDiretion);
		}
	}
}

void Civilian::SetIsDead(bool isDead)
{
	m_IsDead = isDead;
}

bool Civilian::GetIsCultMemeber() const
{
	return m_IsCultMember;
}

bool Civilian::GetIsDead() const
{
	return m_IsDead;
}

Rectf Civilian::GetHitbox() const
{
	return m_Person;
}

int Civilian::GetCultId() const
{
	return m_PersonalCultId;
}

void Civilian::SetIsCultMember(bool IsCultMember)
{
	m_DistanceRange = float(rand() % 50 + 15);
	m_IsCultMember = IsCultMember;
}

void Civilian::MakeNewRandomPosition()
{
	if(m_NewPositionCounter >= m_NEW_POSITION_DElAY)
	{
		m_IsMoving = true;

		int MoveDistance{ 100 };

		if(m_IsCultMember)
		{
			m_NewPosition.x = float(rand() % MoveDistance - MoveDistance / 2) + m_PlayerPosition.x;
			m_NewPosition.y = float(rand() % MoveDistance - MoveDistance / 2) + m_PlayerPosition.y;
		}
		else if (m_IsCultMember == false)
		{
			m_NewPosition.x = float(rand() % MoveDistance - MoveDistance / 2) + m_Position.x;
			m_NewPosition.y = float(rand() % MoveDistance - MoveDistance / 2) + m_Position.y;
		}
		m_NewPositionCounter -= m_NEW_POSITION_DElAY;
	}
	
}

void Civilian::GoToRandomPosition(float elapsedSec, Player::DirectionPlayer PlayerDirection)
{

	float DistanceRangePlayer{1.f};
	float Top{ 715.f };
	float Bottom{ -3.f };
	float Left{ 0.f };
	float Right{1270.f};


	if(m_IsCultMember)
	{
		m_DirectionPlayer = PlayerDirection;

		if(m_DirectionPlayer == Player::DirectionPlayer::Up || m_DirectionPlayer == Player::DirectionPlayer::Down)
		{
			if (m_NewPosition.x < m_Position.x + DistanceRangePlayer && m_NewPosition.x > m_Position.x - DistanceRangePlayer) m_NewPosition.x = m_Position.x;
			else if (m_NewPosition.x > m_Position.x) m_Position.x += m_Speed * elapsedSec;
			else if (m_NewPosition.x < m_Position.x) m_Position.x -= m_Speed * elapsedSec;


			if (m_NewPosition.y < m_Position.y + m_DistanceRange && m_NewPosition.y > m_Position.y - m_DistanceRange) m_NewPosition.y = m_Position.y;
			else if (m_NewPosition.y > m_Position.y) m_Position.y += m_Speed * elapsedSec;
			else if (m_NewPosition.y < m_Position.y) m_Position.y -= m_Speed * elapsedSec;
		}
		else if(m_DirectionPlayer == Player::DirectionPlayer::Left || m_DirectionPlayer == Player::DirectionPlayer::Right)
		{
			if (m_NewPosition.x < m_Position.x + m_DistanceRange && m_NewPosition.x > m_Position.x - m_DistanceRange) m_NewPosition.x = m_Position.x;
			else if (m_NewPosition.x > m_Position.x) m_Position.x += m_Speed * elapsedSec;
			else if (m_NewPosition.x < m_Position.x) m_Position.x -= m_Speed * elapsedSec;


			if (m_NewPosition.y < m_Position.y + DistanceRangePlayer && m_NewPosition.y > m_Position.y - DistanceRangePlayer) m_NewPosition.y = m_Position.y;
			else if (m_NewPosition.y > m_Position.y) m_Position.y += m_Speed * elapsedSec;
			else if (m_NewPosition.y < m_Position.y) m_Position.y -= m_Speed * elapsedSec;
		}
		else
		{
			if (m_NewPosition.x < m_Position.x + m_DistanceRange && m_NewPosition.x > m_Position.x - m_DistanceRange) m_NewPosition.x = m_Position.x;
			else if (m_NewPosition.x > m_Position.x) m_Position.x += m_Speed * elapsedSec;
			else if (m_NewPosition.x < m_Position.x) m_Position.x -= m_Speed * elapsedSec;


			if (m_NewPosition.y < m_Position.y + m_DistanceRange && m_NewPosition.y > m_Position.y - m_DistanceRange) m_NewPosition.y = m_Position.y;
			else if (m_NewPosition.y > m_Position.y) m_Position.y += m_Speed * elapsedSec;
			else if (m_NewPosition.y < m_Position.y) m_Position.y -= m_Speed * elapsedSec;
		}
	}
	else
	{
		if (m_NewPosition.x < m_Position.x + m_DistanceRange && m_NewPosition.x > m_Position.x - m_DistanceRange) m_NewPosition.x = m_Position.x;
		else if (m_NewPosition.x > m_Position.x) m_Position.x += m_Speed * elapsedSec;
		else if (m_NewPosition.x < m_Position.x) m_Position.x -= m_Speed * elapsedSec;


		if (m_NewPosition.y < m_Position.y + m_DistanceRange && m_NewPosition.y > m_Position.y - m_DistanceRange) m_NewPosition.y = m_Position.y;
		else if (m_NewPosition.y > m_Position.y) m_Position.y += m_Speed * elapsedSec;
		else if (m_NewPosition.y < m_Position.y) m_Position.y -= m_Speed * elapsedSec;
	}

	if (m_Position.y <= Bottom)
	{
		m_NewPosition.y = Bottom;
		m_Position.y = Bottom;
	}
	else if (m_Position.y >= Top)
	{
		m_NewPosition.y = Top;
		m_Position.y = Top;
	}

	if(m_Position.x >= Right)
	{
		m_NewPosition.x = Right;
		m_Position.x = Right;
	}
	else if(m_Position.x <= Left)
	{
		m_NewPosition.x = Left;
		m_Position.x = Left;
	}

	if (m_NewPosition.x == m_Position.x && m_NewPosition.y == m_Position.y)
	{
		m_IsMoving = false;
	}
}


