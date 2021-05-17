#include "Game.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>

Game::Game()
	: m_Bird(new Bird()), m_Pipes(new Pipe* [4]), m_Score(0), m_Running(true), m_Offset(4)
{
	std::srand(std::time(nullptr));
	for (int i = 0; i < 4; i++)
	{
		m_Pipes[i] = new Pipe(i+1);
	}

}

Game::~Game()
{
	delete[] m_Pipes;
	delete m_Bird;
}

Bird* Game::GetBird()
{
	return m_Bird;
}

Pipe** Game::GetPipes()
{
	return m_Pipes;
}

void Game::ShowUI(Engine* engine)
{
	//draw score
}

void Game::ShowPipes(Engine* engine)
{
	for (int i = 0; i < 4; i++)
	{
		/*Shape shape = m_Pipes[i]->GetTopShape();
		std::cout << i << std::endl;
		std::cout << shape.x << " " << shape.y << " " << shape.w << " " << shape.h << std::endl;
		shape = m_Pipes[i]->GetBottomShape();
		std::cout << i << std::endl;
		std::cout << shape.x << " " << shape.y << " " << shape.w << " " << shape.h << std::endl;*/

		engine->SetDrawColor(255);
		//std::cout << m_Pipes[i]->GetID() << std::endl;
		engine->Rect(m_Pipes[i]->GetTopShape(), m_Pipes[i]->GetID(), m_Pipes[i]->GetTexture());
		engine->Rect(m_Pipes[i]->GetBottomShape(), -(m_Pipes[i]->GetID()), m_Pipes[i]->GetTexture());
	}
}

bool Game::IsOver()
{
	return !m_Running;
}

void Game::GameOver()
{
	m_Running = false;
}

void Game::ResetPipe(int j)
{
	++m_Offset;
	m_Pipes[j]->SetX((m_Offset - 1) * 300 + 200);
	m_Pipes[j]->Reset();
}
