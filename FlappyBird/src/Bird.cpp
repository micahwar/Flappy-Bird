#include "Bird.h"
#include "engine/Engine.h"
Bird::Bird()
	: m_Pos(glm::vec2(50, 270)), m_Vel(glm::vec2(5, 10)), m_W(50), m_H(50), m_Gravity(1), m_Texture(new Texture("res/textures/bird.png")), m_Bounds(m_Pos.x, m_Pos.y, m_W, m_H), m_BottomScreenBounds(0, -50, 960, 50), m_TopScreenBounds(0, 540, 960, 50)
{
}

void Bird::Show(Engine* engine)
{
	engine->Rotate(m_Vel.y / (10/(glm::pi<float>() / 4)));
	engine->Rect(&m_Bounds, 0, m_Texture);
	engine->SetRotate(0);
}

void Bird::Update()
{ 
	m_Pos += m_Vel;
	m_Vel.y -= m_Gravity;
	m_Bounds.x = m_Pos.x;
	m_Bounds.y = m_Pos.y;
}

void Bird::Jump()
{
	m_Vel.y = 10;
}

bool Bird::ForceCollisions(Pipe* pipe)
{
	return Bird::Collide(pipe->GetBottomShape()) || Bird::Collide(pipe->GetTopShape())
		|| Bird::Collide(&m_BottomScreenBounds) || Bird::Collide(&m_TopScreenBounds);
}

bool Bird::Collide(Shape* bounds)
{
	if ((m_Pos.x > bounds->x && m_Pos.x < bounds->x + bounds->w)
		|| (m_Pos.x + m_W > bounds->x && m_Pos.x + m_W < bounds->x + bounds->w))
	{
		if ((m_Pos.y > bounds->y && m_Pos.y < bounds->y + bounds->h)
			|| (m_Pos.y + m_H > bounds->y && m_Pos.y + m_H < bounds->y + bounds->h))
		{
			return 1;
		}
	}
	return 0;
}
