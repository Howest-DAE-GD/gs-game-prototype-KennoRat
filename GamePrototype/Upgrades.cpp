#include "pch.h"
#include "Upgrades.h"

Upgrades::Upgrades(Point2f Position, float Size, int UpgradeDuplicate) : m_Position{ Position }, m_Size{ Size }
{
	m_IsOn = false;
	m_IsPicked = false;
	m_UpgradeBox = Rectf{ m_Position.x, m_Position.y, m_Size, m_Size };

	m_UpgradeChoice = UpgradeType::AttackSpeed;
	m_ptrTextFont = nullptr;
}

Upgrades::~Upgrades()
{
	delete m_ptrTextFont;
	m_ptrTextFont = nullptr;
}

Upgrades::Upgrades(Point2f Position, float Size): Upgrades(Position, Size, -1)
{

}

void Upgrades::Draw() const
{
	m_ptrTextFont->Draw(Rectf{ m_Position.x- 50.f, m_Position.y + m_Size * 2.f, m_Size * 2.f, m_Size });
	switch (m_UpgradeChoice)
	{
	case Upgrades::UpgradeType::AttackSpeed:
		utils::SetColor(Color4f{0.2f, 0.8f, 0.2f, 1.f});
		utils::DrawRect(m_UpgradeBox);
		break;
	case Upgrades::UpgradeType::AttackDamage:
		utils::SetColor(Color4f{ 0.2f, 0.2f, 0.8f, 1.f });
		utils::DrawRect(m_UpgradeBox);
		break;
	case Upgrades::UpgradeType::PlayerSpeed:
		utils::SetColor(Color4f{ 0.2f, 0.8f, 0.8f, 1.f });
		utils::DrawRect(m_UpgradeBox);
		break;
	case Upgrades::UpgradeType::ExtraArm:
		utils::SetColor(Color4f{ 0.4f, 0.5f, 0.5f, 1.f });
		utils::DrawRect(m_UpgradeBox);
		break;
	case Upgrades::UpgradeType::Dash:
		utils::SetColor(Color4f{ 0.6f, 0.2f, 0.2f, 1.f });
		utils::DrawRect(m_UpgradeBox);
		break;
	}

}

void Upgrades::Update(Rectf PlayerBox)
{
	if(utils::IsOverlapping(m_UpgradeBox, PlayerBox))
	{
		m_IsPicked = true;
	}
}

void Upgrades::NewUpgrades(int UpgradeDuplicate)
{
	do
	{
		m_UpgradeChoice = UpgradeType(rand() % 5);
	} while (m_UpgradeChoice == UpgradeType(UpgradeDuplicate));

	//m_UpgradeChoice = UpgradeType(3);

	m_IsPicked = false;

	std::string m_TextPath{ "NotoSerif-Black.ttf" };
	switch (m_UpgradeChoice)
	{
	case Upgrades::UpgradeType::AttackSpeed:
		m_ptrTextFont = new Texture("AttackSpeed ++", m_TextPath, m_Size, Color4f{ 1.0f, 0.2f, 0.2f, 1.0f });
		break;
	case Upgrades::UpgradeType::AttackDamage:
		m_ptrTextFont = new Texture("AttackDamage ++", m_TextPath, m_Size, Color4f{ 1.0f, 0.2f, 0.2f, 1.0f });
		break;
	case Upgrades::UpgradeType::PlayerSpeed:
		m_ptrTextFont = new Texture("PlayerSpeed ++", m_TextPath, m_Size, Color4f{ 1.0f, 0.2f, 0.2f, 1.0f });
		break;
	case Upgrades::UpgradeType::ExtraArm:
		m_ptrTextFont = new Texture("ExtraArm ++", m_TextPath, m_Size, Color4f{ 1.0f, 0.2f, 0.2f, 1.0f });
		break;
	case Upgrades::UpgradeType::Dash:
		m_ptrTextFont = new Texture("Dash ++", m_TextPath, m_Size, Color4f{ 1.0f, 0.2f, 0.2f, 1.0f });
		break;
	default:
		break;
	}
}

void Upgrades::NewUpgrades()
{
	NewUpgrades(-1);
}

bool Upgrades::GetIsPicked()
{
	return m_IsPicked;
}

int Upgrades::GetUpgradeChoice()
{
	return int(m_UpgradeChoice);
}


