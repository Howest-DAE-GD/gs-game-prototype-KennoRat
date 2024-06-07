#pragma once
#include "utils.h"
#include <Texture.h>
class Upgrades
{
public:
	Upgrades(Point2f Position, float Size);
	Upgrades(Point2f Position, float Size, int UpgradeDuplicate);
	~Upgrades();

	void Draw() const;
	void Update(Rectf PlayerBox);
	void NewUpgrades(int UpgradeDuplicate);
	void NewUpgrades();


	bool GetIsPicked();
	int GetUpgradeChoice();

	enum class UpgradeType
	{
		AttackSpeed, AttackDamage, PlayerSpeed, ExtraArm, Dash
	};

	UpgradeType m_UpgradeChoice;
private:
	Texture* m_ptrTextFont;
	Point2f m_Position;
	bool m_IsOn;
	bool m_IsPicked;
	float m_Size;
	Rectf m_UpgradeBox;
};

