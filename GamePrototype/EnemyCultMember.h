#pragma once
#include <utils.h>
using namespace utils;

class EnemyCultMember
{
public:
	EnemyCultMember(Point2f position, float width, bool IsSpeedy = false, bool IsTanky = false);

	void Draw() const;
	void Update(float elapsedSec, const Point2f& PlayerPosition);
	bool DoHitTest(const Rectf& other);

	Rectf GetHitbox() const;
	bool GetIsDead()const;
private:

	Point2f m_Position;
	Point2f m_NewPosition;
	Point2f m_PlayerPosition;;
	Rectf m_Person{};
	Vector2f m_Velocity;

	bool m_IsMoving;
	bool m_IsDead;
	bool m_IsAgressive;
	bool m_IsTanky;

	int m_Health{ 3 };

	float m_Speed;
	float m_Width;
	float m_Height;

	void MakeNewMovePosition();
	void GoToNewPosition(float elapsedSec, const Point2f& PlayerPosition);
};

