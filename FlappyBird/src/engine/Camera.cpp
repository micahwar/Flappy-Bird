#include "Camera.h"

Camera::Camera(int x, int y)
	: m_Pos(x, y)
{
}

int Camera::GetX()
{
	return m_Pos.x;
}

int Camera::GetY()
{
	return m_Pos.y;
}

void Camera::Move(int x)
{
	m_Pos.x += x;
}