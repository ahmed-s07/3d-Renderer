#include <SDL2/SDL.h>
#include <vector>
#include <cstdint>

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Renderer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH, HEIGHT
    );

    std::vector<uint32_t> pixels(WIDTH * HEIGHT, 0x000000FF);


    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        // clear to black each frame
        std::fill(pixels.begin(), pixels.end(), 0x000000FF);

        // test: draw a red pixel diagonal line
        for (int i = 0; i < 300; i++) {
            put_pixel(i, i, 0xFF0000FF); // RGBA = red
        }

        // push our pixel buffer to the GPU texture, then to screen
        SDL_UpdateTexture(texture, nullptr, pixels.data(), WIDTH * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}