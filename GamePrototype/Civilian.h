#pragma once
#include <utils.h>
#include "Player.h"
using namespace utils;

class Civilian
{
public:
	Civilian(Point2f position, float width, bool IsCultMember = false);

	void Draw() const;
	void Update(float elapsedSec, const Point2f& PlayerPosition, Player::DirectionPlayer PlayerDiretion);

	bool GetIsCultMemeber() const;
	bool GetIsDead() const;
	Rectf GetHitbox() const;
	int GetCultId() const;

	void SetIsDead(bool IsDead);
	void SetIsCultMember(bool IsCultMember);
	
	static int m_CultID;

private:

	
	Player::DirectionPlayer m_DirectionPlayer;

	Point2f m_Position;
	Point2f m_NewPosition;
	Point2f m_PlayerPosition;;
	Rectf m_Person{};

	bool m_IsMoving;
	bool m_IsCultMember;
	bool m_IsDead;
	int m_PersonalCultId;

	float m_DistanceRange;
	float m_Speed;
	float m_Width;

	float m_NewPositionCounter;
	float m_NEW_POSITION_DElAY{1.f};

	void MakeNewRandomPosition();
	void GoToRandomPosition(float elapsedSec, Player::DirectionPlayer PlayerDiretion);
};

