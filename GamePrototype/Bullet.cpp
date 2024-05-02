#include "pch.h"
#include "Bullet.h"


Bullet::Bullet(float width, float height, const Rectf& fieldBoundaries, const Point2f& MousePosition, const Point2f& center) : m_Width{ width }, m_Height{ height }, m_FieldBoundaries{fieldBoundaries}, m_MousePosition{MousePosition}, m_Center{center}
{
	Vector2f BulletDirection{ (MousePosition.x - center.x), (MousePosition.y - center.y) };
	m_Velocity = Vector2f{ BulletDirection.x / sqrtf(BulletDirection.x * BulletDirection.x + BulletDirection.y * BulletDirection.y) , BulletDirection.y / sqrtf(BulletDirection.x * BulletDirection.x + BulletDirection.y * BulletDirection.y) };
	m_IsActivated = true;
}

void Bullet::Draw() const
{
	if (m_IsActivated)
	{
		SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.f });
		utils::FillRect(Rectf{ m_Center.x, m_Center.y, m_Width, m_Height });
	}
}

void Bullet::Update(float elapsedSec, std::vector<EnemyCultMember*>& enemies)
{
	if (m_IsActivated)
	{
		m_Center.x += m_Velocity.x * 500.f * elapsedSec;
		m_Center.y += m_Velocity.y * 500.f * elapsedSec;
		CheckBoundaries();
		CheckEnemiesHit(enemies);
	}
}

void Bullet::SetDimesnions(float width, float height)
{
	m_Height = height;
	m_Width = width;
}

void Bullet::SetFieldBoundaries(const Rectf& fieldBoundaries)
{
	m_FieldBoundaries = fieldBoundaries;
}

bool Bullet::GetIsActivated() const
{
	return m_IsActivated;
}

void Bullet::CheckBoundaries()
{
	if (m_Center.y > m_FieldBoundaries.height)
	{
		m_IsActivated = false;
	}
}

void Bullet::CheckEnemiesHit(std::vector<EnemyCultMember*>& enemies)
{
	Rectf Bullet = Rectf{ m_Center.x, m_Center.y, m_Width, m_Height };
	for (EnemyCultMember* EnemyIndex : enemies)
	{
		if(EnemyIndex->GetIsDead() == false)
		{
			if (EnemyIndex->DoHitTest(Bullet))
			{
				m_IsActivated = false;
			}
		}
	}
}
