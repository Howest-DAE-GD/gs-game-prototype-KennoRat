#pragma once
#include <Texture.h>
#include <iostream>
#include "Vector2f.h"
#include "utils.h"
class Text
{
public:
	Text(Point2f Position, float Width, float Height, const std::string& Text);
	~Text();;

	void Draw() const;
	void Update(float elapsedSec);
	void ChangeText(const std::string& NewText);

	bool GetIsDone();
	bool GetGameEnd();

	void SetGameEnd(bool GameEnd);

private:
	Texture* m_ptrTextFont;
	bool m_GameEnd;
	bool m_IsDone;
	Point2f m_Position;
	float m_Width;
	float m_Height;

	float m_TimeCounter;
	const float m_MAX_TIME_DELAY{5.f};
};

