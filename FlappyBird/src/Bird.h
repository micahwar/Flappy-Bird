#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "Pipe.h"

class Bird
{
private:
	glm::vec2 m_Pos;
	glm::vec2 m_Vel;
	int m_H;
	int m_W;
	int m_Gravity;
	Texture* m_Texture;
	Shape m_Bounds;
	Shape m_BottomScreenBounds;
	Shape m_TopScreenBounds;
public:
	Bird();
	~Bird() {}

	void Show(Engine* engine);
	void Update();
	bool ForceCollisions(Pipe* pipe);
	void Jump();
private:
	bool Collide(Shape* bounds);
};