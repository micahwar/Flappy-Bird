#pragma once

#include "Bird.h"
#include "Pipe.h"
#include "engine/Engine.h"

class Game
{
private:
	Bird* m_Bird;
	Pipe** m_Pipes;
	int m_Score;
	bool m_Running;
	int m_Offset;
public:
	Game();
	~Game();

	Bird* GetBird();
	Pipe** GetPipes();
	void ShowUI(Engine* engine);
	void ShowPipes(Engine* engine);
	bool IsOver();
	void GameOver();
	void ResetPipe(int j);
};