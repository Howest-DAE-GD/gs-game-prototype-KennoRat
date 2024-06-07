#pragma once
#include <utils.h>
#include <iostream>
#include <vector>
using namespace utils;

class Player
{
public:
	Player(Point2f position, float width);

	void Draw() const;
	void Update(float elapsedSec, bool IsLeft,bool IsDown, bool IsRight , bool IsUP);
	void IncrementCultMembers();
	void DecrementCultMembers();
	void SacrificeCultMemberTimer();
	void PlusSpeed();

	void SetSacrificeAvailable(bool Sacrifice);
	void SetIsDead(bool IsDead);
	void SetIsDashing(bool IsDashing);

	bool GetIsDead();
	bool GetSacrificeAvailable();
	bool GetIsDashing() const;
	int GetTotalCultMembers();
	int GetCultMembers();
	Point2f GetPosition() const;
	Rectf GetHitbox() const;

	enum class DirectionPlayer
	{
		Up, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft
	};

	DirectionPlayer m_Direction;


private:
	Point2f m_Position;

	Rectf m_Player {};

	bool m_SacrificeAvailable;
	bool m_IsDead;
	bool m_IsDashing;
	int m_TotalCultMembers;
	int m_CultMembers;
	float m_Speed;
	float m_Width;

	float m_DashCounter;
	float m_DASH_MAX{0.15f};

	float m_SacrificeCultMemberDelayCounter{};
	float m_SACRIFICE_CULT_MAX{1.f};

	std::vector<Point2f> m_DashPoints;

	void DashCounter(float elapsedSec);
};

