#pragma once

#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
	glm::vec2 m_Pos;
public:
	Camera(int x, int y);
	~Camera() {}

	int GetX();
	int GetY();
	void Move(int x);
};