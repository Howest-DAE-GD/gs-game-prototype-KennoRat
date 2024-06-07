#pragma once
#include <Texture.h>
#include <iostream>
#include "Vector2f.h"
#include "utils.h"
class UI
{
public:
	UI(Point2f Position, float Width, float Height);
	~UI();;

	void Draw() const;
	void Update(float elapsedSec, int Sacrificed, int DashAmount);


private:
	const std::string m_TextSacrificed{"People fed: "};
	Texture* m_ptrTextFont;
	Texture* m_ptrDashFont;
	Point2f m_Position;
	int m_Sacrificed;
	int m_DashAmount;
	float m_Width;
	float m_Height;
};

