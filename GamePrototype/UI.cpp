#include "pch.h"
#include "UI.h"

UI::UI(Point2f Position, float Width, float Height): m_Position{Position}, m_Width{Width}, m_Height{Height}
{
	std::string m_TextPath{ "NotoSerif-Black.ttf" };
	m_Sacrificed = 0;
	m_DashAmount = 0;
	m_ptrTextFont = new Texture(m_TextSacrificed + " " + std::to_string(m_Sacrificed), m_TextPath, m_Height, Color4f{1.0f, 0.2f, 0.2f, 1.0f});
	m_ptrDashFont = new Texture(" Dash: ", m_TextPath, m_Height, Color4f{ 0.8f, 0.8f, 0.8f, 1.0f });
}

UI::~UI()
{
	delete m_ptrTextFont;
	m_ptrTextFont = nullptr;
	delete m_ptrDashFont;
	m_ptrDashFont = nullptr;
}

void UI::Draw() const
{
	m_ptrTextFont->Draw(Rectf{ m_Position.x, m_Position.y, m_Width, m_Height });
	m_ptrDashFont->Draw(Rectf{ m_Position.x + 300.f, m_Position.y, m_Width/2.f, m_Height });
	if (m_DashAmount > 0)
	{
		for(int DashIndex{}; DashIndex < m_DashAmount; ++DashIndex)
		{
			utils::DrawEllipse(Point2f(m_Position.x + 420.f + (DashIndex * 50.f), m_Position.y + m_Height / 2.f), m_Height/4.f, m_Height / 4.f);
		}
	}
}

void UI::Update(float elapsedSec, int Sacrificed, int DashAmount)
{
	delete m_ptrTextFont;
	m_ptrTextFont = nullptr;
	m_Sacrificed = Sacrificed;
	m_DashAmount = DashAmount;
	std::string m_TextPath{ "NotoSerif-Black.ttf" };
	m_ptrTextFont = new Texture(m_TextSacrificed + " " + std::to_string(m_Sacrificed), m_TextPath, m_Height, Color4f{ 0.8f, 0.8f, 0.8f, 1.0f });
}
