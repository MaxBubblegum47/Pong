#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "util.h"
#include "vector.h"  // Add this for Vec2

// Remove this line - it's creating a global variable!
// SDL_Renderer* renderer;

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
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);

            SDL_RenderFillRect(renderer, &rect);
        }

        void Update(float dt)
        {
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