#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "engine/Engine.h"
#include "engine/Window.h"
#include "Game.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "KeyEvent.h"

int main(void)
{
    Window* window;
    if (!glfwInit())
        return -1;

    window = new Window(960, 540, "Flappy Bird");

    if (!window->HasValidContext())
    {
        glfwTerminate();
        return -1;
    }

    window->Init();

    if (glewInit() != GLEW_OK)
        return -1;


    {
        Game game = Game();
        Engine engine(960, 540);
        KeyEvent keyEvent = KeyEvent(window->GetWindow());
        Texture* backgroundImage = new Texture("res/textures/background.png");
        double lasttime = glfwGetTime();
        while (!window->ShouldClose())
        {
            engine.Clear();
            //engine.Background(51);
            engine.Background(backgroundImage);
            //engine.Rect(Shape(0, 0))
            engine.SetDrawColor(255);
            engine.MoveCamera(-5);
            game.GetBird()->Update();
            if (keyEvent.SpacePressed())
            {
                game.GetBird()->Jump();
            }

            for (int i = 0; i < 4; i++)
            {
                if (game.GetBird()->ForceCollisions(game.GetPipes()[i]))
                    game.GameOver();
            }

            if (game.IsOver())
            {
                //bad things
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    if (game.GetPipes()[i]->IsOutsideBounds(&engine))
                    {
                        game.ResetPipe(i);
                    }
                }
                game.ShowPipes(&engine);
                engine.SetDrawColor(255, 0, 0);
                game.GetBird()->Show(&engine);
            }
            
            game.ShowUI(&engine);
            window->SwapBuffers();
            window->PollEvents();
            while (glfwGetTime() < lasttime + 1.0 / 60) {
                // game intensly
            }
            lasttime += 1.0 / 60;
        }
    }
    window->OnClose();
    return 0;
}