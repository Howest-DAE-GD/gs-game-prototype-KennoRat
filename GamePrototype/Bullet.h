#pragma once
#include "Vector2f.h"
#include "utils.h"
#include <math.h>
#include "EnemyCultMember.h"


class Bullet
{
public:
	Bullet(float width, float height, const Rectf& fieldBoundaries, const Point2f& MousePosition, const Point2f& center, int AttackDamage);

	void Draw() const;
	void Update(float elapsedSec, std::vector<EnemyCultMember*>& enemies);
	void SetDimesnions(float width, float height);
	void SetFieldBoundaries(const Rectf& fieldBoundaries);

	bool GetIsActivated() const;

private:
	Point2f m_MousePosition;
	Point2f m_Center{};
	int m_Health;
	float m_Width;
	float m_Height;
	Vector2f m_Velocity;
	Rectf m_FieldBoundaries;
	bool m_IsActivated;

	void CheckBoundaries();
	void CheckEnemiesHit(std::vector<EnemyCultMember*>& enemies);
};

