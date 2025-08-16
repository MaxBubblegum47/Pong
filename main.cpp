#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <chrono>
#include "vector.h"
#include "ball.h"
#include "paddle.h"
#include "playerscore.h"
#include "util.h"
#include "collision.h"

enum Buttons 
{
	PaddleOneUp = 0,
	PaddleOneDown,
	PaddleTwoUp,
	PaddleTwoDown,
};

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("Pong",0,0,WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Create the ball
    Ball ball(
        Vec2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f),
        Vec2(BALL_SPEED, 0.0f));

	// Create the paddles
	Paddle paddleOne(
		Vec2(50.0f, WINDOW_HEIGHT / 2.0f),
		Vec2(0.0f, 0.0f));

	Paddle paddleTwo(
		Vec2(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2.0f),
		Vec2(0.0f, 0.0f));

	// If you don't see anything written on screen is because of the program is not finding the font!
	TTF_Font* scoreFont = TTF_OpenFont("/Users/utente/Desktop/coding/Pong/build/dejavu-fonts-ttf-2.37/ttf/DejaVuSans.ttf", 40);
	if (!scoreFont) {
    	printf("TTF_OpenFont failed: %s\n", TTF_GetError());
    	// Try a different font or handle the error
	}

	PlayerScore playerOneScoreText(Vec2(WINDOW_WIDTH / 4, 20), renderer, scoreFont);
	PlayerScore playerTwoScoreText(Vec2(3 * WINDOW_WIDTH / 4, 20), renderer, scoreFont);

	// Replace your game logic section with this fixed version:

// Game Logic
{    
    bool running = true;
    bool buttons[4] = {};
    float dt = 0.0f;
    
    while(running)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;    
            } 
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
                // paddle movements logic
                else if (event.key.keysym.sym == SDLK_w)
                {
                    buttons[Buttons::PaddleOneUp] = true;
                }
                else if (event.key.keysym.sym == SDLK_s)
                {
                    buttons[Buttons::PaddleOneDown] = true;
                } 
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    buttons[Buttons::PaddleTwoUp] = true;
                } 
                else if (event.key.keysym.sym == SDLK_DOWN)
                {
                    buttons[Buttons::PaddleTwoDown] = true;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                if (event.key.keysym.sym == SDLK_w)
                {
                    buttons[Buttons::PaddleOneUp] = false;
                }
                else if (event.key.keysym.sym == SDLK_s)
                {
                    buttons[Buttons::PaddleOneDown] = false;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    buttons[Buttons::PaddleTwoUp] = false;
                }
                else if (event.key.keysym.sym == SDLK_DOWN)
                {
                    buttons[Buttons::PaddleTwoDown] = false;
                }
            }
        }

        if (buttons[Buttons::PaddleOneUp])
        {
            paddleOne.velocity.y = -PADDLE_SPEED;
        }
        else if (buttons[Buttons::PaddleOneDown])
        {
            paddleOne.velocity.y = PADDLE_SPEED;
        } else
        {
            paddleOne.velocity.y = 0.0f;
        }

        if (buttons[Buttons::PaddleTwoUp])
        {
            paddleTwo.velocity.y = -PADDLE_SPEED;
        }
        else if (buttons[Buttons::PaddleTwoDown])
        {
            paddleTwo.velocity.y = PADDLE_SPEED;
        }
        else
        {
            paddleTwo.velocity.y = 0.0f;
        }
        
        // Update ALL game objects
        paddleOne.Update(dt);
        paddleTwo.Update(dt);
        ball.Update(dt);

        // Cheks collisions
        if (Contact contact = CheckPaddleCollision(ball, paddleOne); contact.type != CollisionType::None)
        {
            ball.CollideWithPaddle(contact);
        }
        else if (Contact contact = CheckPaddleCollision(ball, paddleTwo); contact.type != CollisionType::None)
        {
            ball.CollideWithPaddle(contact);
        }
        else if (Contact contact = CheckWallCollision(ball); contact.type != CollisionType::None)
        {
        	ball.CollideWithWall(contact);
        }

        // Make the whole window black
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(renderer);
    
        // Rendering zone
        // The main stage
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) ;
        
        for (int y = 0; y < WINDOW_HEIGHT; ++y)
        {
            if (y % 5)
            {
                SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
            }
        }
        
        // Draw the ball
        ball.Draw(renderer);
        paddleOne.Draw(renderer);
        paddleTwo.Draw(renderer);
        playerOneScoreText.Draw();
        playerTwoScoreText.Draw();

        // Present the backbuffer
        SDL_RenderPresent(renderer);

        // Calculate frame time (convert to seconds)
        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float>(stopTime - startTime).count();
        
        // Add a small delay to prevent excessive CPU usage
        SDL_Delay(1);
    }
}	

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(scoreFont);
	TTF_Quit();
	SDL_Quit();

	return 0;
}
