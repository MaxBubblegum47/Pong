#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <chrono>

class PlayerScore
{
    public:
        PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font): renderer(renderer), font(font)
        {
            surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
            texture = SDL_CreateTextureFromSurface(renderer, surface);

            int widht, height;
            SDL_QueryTexture(texture, nullptr, nullptr, &widht, &height);

            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.w = widht;
            rect.h = height;
        }

        ~PlayerScore()
        {
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        void Draw()
        {
		    SDL_RenderCopy(renderer, texture, nullptr, &rect);
        }

        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Surface* surface{};
        SDL_Texture* texture{};
        SDL_Rect rect{};
};