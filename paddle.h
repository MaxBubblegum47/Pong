#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// utilities
SDL_Renderer* renderer;
const int PADDLE_HEIGHT = 100;
const int PADDLE_WIDTH = 25;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

class Paddle 
{
    public:
        Paddle(Vec2 position, Vec2 velocity) : position(position), velocity(velocity)
        {
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = PADDLE_WIDTH;
            rect.h = PADDLE_HEIGHT;
        }

        void Draw(SDL_Renderer* renderer)
        {
            rect.x = static_cast<int>(position.x); // Update x position too
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }

        void Update(float dt)
        {
            // FIXED: Use velocity instead of position!
            position += velocity * dt;

            // Boundary checking
            if (position.y < 0)
            {
                position.y = 0;
            } 
            else if (position.y > (WINDOW_HEIGHT - PADDLE_HEIGHT)) 
            {
                position.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
            }
        }

        Vec2 position;
        Vec2 velocity;
        SDL_Rect rect{};
};