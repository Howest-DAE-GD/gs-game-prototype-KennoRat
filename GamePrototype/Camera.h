#pragma once
class Camera
{
public:
	explicit Camera(float screenWidth, float screenHeight);

	void Aim(float levelWidth, float levelHeight, const Point2f& trackCenter);
	void Reset();

	Point2f GetBottomLeftPosition() const;

private:
	float m_ScreenWidth;
	float m_ScreenHeight;
	Point2f m_BottomLeftPosition;
};

