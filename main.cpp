#include <SDL2/SDL.h>
#include "vector.h"
#include "ball.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Pong",0,0,WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Create the ball
	Ball ball(
			Vec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f),
				(WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f)));

	// Game Logic
	{
		bool running = true;

		while(running)
		{
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
				}
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

			// Present the backbuffer
			SDL_RenderPresent(renderer);
		}
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
