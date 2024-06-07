#include "pch.h"
#include "EnemyCultMember.h"

EnemyCultMember::EnemyCultMember(Point2f position, float width, bool IsSpeedy, bool IsTanky): m_Position{position}, m_Width(width)
{
	m_Speed = 50.f;
	m_Person = Rectf{ m_Position.x, m_Position.y, m_Width, m_Width };
	m_IsMoving = false;
	m_IsDead = false;
	m_IsTanky = false;
	m_Height = 0.f;

	int RandomIsAgressive{};
	if(IsSpeedy)
	{
		RandomIsAgressive = rand() % 2;
	}
	else
	{
		RandomIsAgressive = 1;
	}


	if(RandomIsAgressive == 0)
	{
		m_IsAgressive = true;
		m_Height = 10.f;
	}
	else
	{
		m_IsAgressive = false;

		int RandomIsTanky{};

		if(IsTanky)
		{
			RandomIsTanky = rand() % 2;
		}
		else
		{
			RandomIsTanky = 1;
		}


		if (RandomIsTanky == 0)
		{
			m_IsTanky = true;
			m_Width += 15.f;
		}
		else m_IsTanky = false;
	}
}

void EnemyCultMember::Draw() const
{
	if (m_IsDead == false)
	{
		if(m_IsAgressive)
		{
			SetColor(Color4f{ 0.6f, 0.5f, 0.5f, 1.f });
		}
		else
		{
			SetColor(Color4f{ 0.8f, 0.4f, 0.4f, 1.f });
		}

		if(m_IsTanky)
		{
			SetColor(Color4f{ 0.8f, 0.2f, 0.2f, 1.f });
			FillRect(m_Person);
		}
		else
		{
			FillRect(m_Person);
		}

	}
}

void EnemyCultMember::Update(float elapsedSec, const Point2f& PlayerPosition)
{
	m_Person = Rectf{ m_Position.x, m_Position.y, m_Width, m_Width + m_Height };
	m_PlayerPosition = PlayerPosition;
	m_NewPosition = m_PlayerPosition;

	GoToNewPosition(elapsedSec, PlayerPosition);
}

bool EnemyCultMember::DoHitTest(const Rectf& other)
{
	if (utils::IsOverlapping(other, m_Person))
	{
		if(m_IsTanky)
		{
			if(m_Health == 1)
			{
				m_IsDead = true;
			}
			--m_Health;
		}
		else
		{
			m_IsDead = true;
		}

		return true;
	}
	else
	{
		return false;
	}
}

Rectf EnemyCultMember::GetHitbox() const
{
	return m_Person;
}

bool EnemyCultMember::GetIsDead() const
{
	return m_IsDead;
}

void EnemyCultMember::MakeNewMovePosition()
{
}

void EnemyCultMember::GoToNewPosition(float elapsedSec, const Point2f& PlayerPosition)
{
	float DistanceRange{ 0.f };
	float Top{ 715.f };
	float Bottom{ -3.f };
	float Left{ 0.f };
	float Right{ 1270.f };
	float AgressiveSpeed{200.f};

	Vector2f BulletDirection{ (PlayerPosition.x - m_Position.x), (PlayerPosition.y - m_Position.y) };
	m_Velocity = Vector2f{ BulletDirection.x / sqrtf(BulletDirection.x * BulletDirection.x + BulletDirection.y * BulletDirection.y) , BulletDirection.y / sqrtf(BulletDirection.x * BulletDirection.x + BulletDirection.y * BulletDirection.y) };

	if(m_IsAgressive)
	{
		m_Position.x += m_Velocity.x * AgressiveSpeed * elapsedSec;
		m_Position.y += m_Velocity.y * AgressiveSpeed * elapsedSec;
	}
	else
	{
	/*	if (m_NewPosition.x < m_Position.x + DistanceRange && m_NewPosition.x > m_Position.x - DistanceRange) m_NewPosition.x = m_Position.x;
		else if (m_NewPosition.x > m_Position.x) m_Position.x += m_Speed * elapsedSec;
		else if (m_NewPosition.x < m_Position.x) m_Position.x -= m_Speed * elapsedSec;


		if (m_NewPosition.y < m_Position.y + DistanceRange && m_NewPosition.y > m_Position.y - DistanceRange) m_NewPosition.y = m_Position.y;
		else if (m_NewPosition.y > m_Position.y) m_Position.y += m_Speed * elapsedSec;
		else if (m_NewPosition.y < m_Position.y) m_Position.y -= m_Speed * elapsedSec;

		if (m_NewPosition.x == m_Position.x && m_NewPosition.y == m_Position.y)
		{
			m_IsMoving = false;
		}*/

		m_Position.x += m_Velocity.x * m_Speed * elapsedSec;
		m_Position.y += m_Velocity.y * m_Speed * elapsedSec;
	}


	//if (m_Position.y <= Bottom)
	//{
	//	m_NewPosition.y = Bottom;
	//	m_Position.y = Bottom;
	//}
	//else if (m_Position.y >= Top)
	//{
	//	m_NewPosition.y = Top;
	//	m_Position.y = Top;
	//}

	//if (m_Position.x >= Right)
	//{
	//	m_NewPosition.x = Right;
	//	m_Position.x = Right;
	//}
	//else if (m_Position.x <= Left)
	//{
	//	m_NewPosition.x = Left;
	//	m_Position.x = Left;
	//}
}
