#pragma once
#include "Shape.h"
#include "engine/Engine.h"
#include <random>

class Pipe
{
private:
	int m_PosX;
	int m_GapY;
	int m_ID;
	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> dist;
	Texture* m_Texture;
	Shape m_BottomShape;
	Shape m_TopShape;

public:
	const static int GapSize = 180;

	Pipe(int x);
	~Pipe() {}

	void Show(Engine* engine);
	bool IsOutsideBounds( Engine* engine);
	Shape* GetTopShape();
	Shape* GetBottomShape();
	int GetID();
	Texture* GetTexture();
	void SetX(int x);
	void Reset();
	int GetX();
};