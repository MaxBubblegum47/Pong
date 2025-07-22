#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

class Ball
{
	public:
		Ball(Vec2 position) : position(position)
		{
			rect.x = static_cast<int>(position.x);
			rect.y = static_cast<int>(position.y);
			rect.w = BALL_WIDTH;
			rect.h = BALL_HEIGHT;
		}

		void Draw(SDL_Renderer* renderer)
		{
			rect.x = static_cast<int>(position.x);
			rect.y = static_cast<int>(position.y);

			SDL_RenderFillRect(renderer, &rect);
		}

		Vec2 position;
		SDL_Rect rect{};

};
