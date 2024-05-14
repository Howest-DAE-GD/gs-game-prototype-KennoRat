#include "pch.h"
#include "Text.h"

Text::Text(Point2f Position, float Width, float Height, const std::string& Text):m_Position{Position}, m_Width{Width}, m_Height{Height}
{
	m_IsDone = false;
	std::string m_TextPath{ "NotoSerif-Black.ttf" };
	m_ptrTextFont = new Texture(Text, m_TextPath, m_Height, Color4f{1.0f, 0.2f, 0.2f, 1.0f});
	m_TimeCounter = 0.f;
	m_GameEnd = false;
}

Text::~Text()
{
	delete m_ptrTextFont;
	m_ptrTextFont = nullptr;
}

void Text::Draw() const
{
	if(m_IsDone == false || m_GameEnd == true) m_ptrTextFont->Draw(Rectf{ m_Position.x, m_Position.y, m_Width, m_Height});
}

void Text::Update(float elapsedSec)
{
	m_TimeCounter += elapsedSec;
	//std::cout << m_TimeCounter << std::endl;
	if(m_TimeCounter >= m_MAX_TIME_DELAY)
	{
		m_IsDone = true;
	}
}

void Text::ChangeText(const std::string& NewText)
{
	delete m_ptrTextFont;
	m_ptrTextFont = nullptr;
	std::string m_TextPath{ "NotoSerif-Black.ttf" };
	m_ptrTextFont = new Texture(NewText, m_TextPath, m_Height, Color4f{ 1.0f, 0.2f, 0.2f, 1.0f });
}

bool Text::GetIsDone()
{
	return m_IsDone;
}

bool Text::GetGameEnd()
{
	return m_GameEnd;
}

void Text::SetGameEnd(bool GameEnd)
{
	m_GameEnd = GameEnd;
}
