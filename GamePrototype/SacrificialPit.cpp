#include "pch.h"
#include "SacrificialPit.h"

SacrificialPit::SacrificialPit(Point2f position, float width): m_Position{position}, m_Width{width}
{
	m_SacrificeBox = Rectf( m_Position.x - m_Width / 4.f, m_Position.y - m_Width / 4.f, m_Width / 2.f, m_Width / 2.f );
	m_SacrificedCultMembers = 0;

	double angleIncrement = 2.0 * M_PI / 5.0;
	
	for (int Pointindex = 0; Pointindex < 5; ++Pointindex) {
		double angle = Pointindex * angleIncrement;
		double x = m_Position.x + m_Width * cos(angle);
		double y = m_Position.y + m_Width * sin(angle);

		m_PentagonPoints.push_back(Point2f(x, y));
	}
}

void SacrificialPit::Draw() const
{
	SetColor(Color4f{0.8f, 0.4f, 0.4f, 1.0f});
	DrawEllipse(m_Position, m_Width, m_Width, 2.f);
	DrawRect(m_SacrificeBox);

	float Radius{ 5.f };
	for (Point2f Points : m_PentagonPoints)
	{
		FillEllipse(Points, Radius, Radius);
	}

	float LineWidth{4.f};

	if(m_SacrificedCultMembers >= 90)
	{
		DrawLine(m_PentagonPoints[0], m_PentagonPoints[2], LineWidth);
	}

	if (m_SacrificedCultMembers >= 80)
	{
		DrawLine(m_PentagonPoints[2], m_PentagonPoints[4], LineWidth);
	}

	if (m_SacrificedCultMembers >= 70)
	{
		DrawLine(m_PentagonPoints[4], m_PentagonPoints[1], LineWidth);
	}

	if (m_SacrificedCultMembers >= 60)
	{
		DrawLine(m_PentagonPoints[1], m_PentagonPoints[3], LineWidth);
	}

	if (m_SacrificedCultMembers >= 50)
	{
		DrawLine(m_PentagonPoints[3], m_PentagonPoints[0], LineWidth);
	}

	if (m_SacrificedCultMembers >= 40)
	{
		//FillArc(m_Position.x, m_Position.y, m_Width, m_Width, 0.f, 6.3f);
		float ExtraWidth{ 20.f };
		DrawEllipse(m_Position, m_Width + ExtraWidth, m_Width + ExtraWidth, 2.f);
	}
	else if (m_SacrificedCultMembers >= 30)
	{
		//FillArc(m_Position.x, m_Position.y, m_Width, m_Width, 0.f, 4.68f);
		float ExtraWidth{ 15.f };
		DrawEllipse(m_Position, m_Width + ExtraWidth, m_Width + ExtraWidth, 2.f);
	}
	else if(m_SacrificedCultMembers >= 20)
	{
		//FillArc(m_Position.x, m_Position.y, m_Width, m_Width, 0.f, 3.12f);
		float ExtraWidth{ 10.f };
		DrawEllipse(m_Position, m_Width + ExtraWidth, m_Width + ExtraWidth, 2.f);
	}
	else if(m_SacrificedCultMembers >= 10)
	{
		//FillArc(m_Position.x, m_Position.y, m_Width, m_Width, 0.f, 1.56f);
		float ExtraWidth{ 5.f };
		DrawEllipse(m_Position, m_Width + ExtraWidth, m_Width + ExtraWidth, 2.f);
	}
}

void SacrificialPit::Update(float elapsedSec)
{
}

void SacrificialPit::IncrementSacrificedCultMembers()
{
	++m_SacrificedCultMembers;
}

int SacrificialPit::GetSacrificedCultMembers()
{
	return m_SacrificedCultMembers;
}

Rectf SacrificialPit::GetSacrificeBox()
{
	return m_SacrificeBox;
}
