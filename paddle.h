#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// utilities
SDL_Renderer* renderer;
const int PADDLE_HEIGHT = 100;
const int PADDLE_WIDTH = 25;

class Paddle 
{
    public:
        Paddle(Vec2 position) : position(position)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = PADDLE_WIDTH;
            rect.h = PADDLE_HEIGHT;
        }

        void Draw(SDL_Renderer* renderer)
        {
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }

        Vec2 position;
        SDL_Rect rect{};
};