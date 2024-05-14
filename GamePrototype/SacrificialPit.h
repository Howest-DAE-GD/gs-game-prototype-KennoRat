#pragma once
#include <utils.h>
#include <vector>
#include <math.h>


using namespace utils;

class SacrificialPit
{
public:
	SacrificialPit(Point2f position, float width);

	void Draw() const;
	void Update(float elapsedSec);

	void IncrementSacrificedCultMembers();
	int GetSacrificedCultMembers();
	Rectf GetSacrificeBox();

private:

	std::vector<Point2f> m_PentagonPoints;
	Point2f m_Position;
	Rectf m_SacrificeBox;
	float m_Width;
	int m_SacrificedCultMembers;
};

