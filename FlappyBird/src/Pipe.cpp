#include "Pipe.h"
#include <stdlib.h>
#include <iostream>
Pipe::Pipe(int id)
	: m_PosX((id - 1) * 300 + 200), m_ID(id), m_Texture(new Texture("res/textures/pipe.png")), m_GapY(0)
{
	std::random_device dev;
	rng = std::mt19937(dev());
	dist = std::uniform_int_distribution<std::mt19937::result_type>(50, 540-GapSize-50);
	Reset();
}

void Pipe::Reset()
{

	m_GapY = dist(rng);
	
	//m_BottomShape = Shape(m_PosX, 0, 50, 540 - GapSize - m_GapY);
	//m_TopShape = Shape(m_PosX, m_GapY + GapSize, 50, 540 - GapSize - (540 - GapSize - m_GapY));
	m_TopShape = Shape(m_PosX, m_GapY + GapSize, 50, 540 - GapSize - m_GapY);
	m_BottomShape = Shape(m_PosX, 0, 50, m_GapY);
	
}

bool Pipe::IsOutsideBounds(Engine* engine) 
{	
	if (m_PosX + 50 < abs(engine->GetCameraX()))
	{
		return 1;
	}
	return 0;
}

void Pipe::SetX(int x)
{
	m_PosX = x;
	m_ID += 4;
}

int Pipe::GetX()
{
	return m_PosX;
}

Texture* Pipe::GetTexture()
{
	return m_Texture;
}

Shape* Pipe::GetTopShape()
{
	return &m_TopShape;
}

Shape* Pipe::GetBottomShape()
{
	return &m_BottomShape;
}

int Pipe::GetID()
{
	return m_ID;
}