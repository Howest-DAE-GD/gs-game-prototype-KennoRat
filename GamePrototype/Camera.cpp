#include "pch.h"
#include "Camera.h"

Camera::Camera(float screenWidth, float screenHeight) : m_ScreenWidth{ screenWidth }, m_ScreenHeight{screenHeight}
{
	m_BottomLeftPosition = Point2f{ 0.f, 0.f };
}

void Camera::Aim(float levelWidth, float levelHeight, const Point2f& trackCenter)
{
	Point2f bottomLeftPosition{ trackCenter.x - m_ScreenWidth/2.f, trackCenter.y - m_ScreenHeight/2.f};

	if(bottomLeftPosition.x + m_ScreenWidth >= levelWidth)
	{
		bottomLeftPosition.x = levelWidth - m_ScreenWidth;
	}
	else if(bottomLeftPosition.x <= -320.f)
	{
		bottomLeftPosition.x = -320.f;
	}

	if(bottomLeftPosition.y + m_ScreenHeight >= levelHeight)
	{
		bottomLeftPosition.y = levelHeight - m_ScreenHeight;
	}
	else if (bottomLeftPosition.y <= -180.f)
	{
		bottomLeftPosition.y = -180.f;
	}

	m_BottomLeftPosition = bottomLeftPosition;

	glPushMatrix();
	glTranslatef(-bottomLeftPosition.x, -bottomLeftPosition.y, 0);
}

void Camera::Reset()
{
	glPopMatrix();
}

Point2f Camera::GetBottomLeftPosition() const
{
	return m_BottomLeftPosition;
}
