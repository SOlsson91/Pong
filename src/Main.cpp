#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "./Paddle.h"
#include "./Ball.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000.0f / FPS;

int WIDTH = 1280;
int HEIGHT = 720;
bool isRunning = false;
int playerScore = 0;
int opponentScore = 0;
std::unique_ptr<Paddle> player = std::make_unique<Paddle>(30, HEIGHT / 2, 30, 100);
std::unique_ptr<Paddle> opponent = std::make_unique<Paddle>(WIDTH - 60, HEIGHT / 2, 30, 100);
std::unique_ptr<Ball> ball = std::make_unique<Ball>(WIDTH / 2, HEIGHT /2, 15, 15);

bool InitializeSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING == 0))
    {
        std::cout << "Error Initializing SDL" << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        std::cout << "Error creating SDL Window." << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Error creating SDL Renderer." << std::endl;
        return false;
    }
    return true;
}

void ProcessInput()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = false;
                }

                break;

            default:
                break;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
    {
        if (player->GetRect()->y >= 0)
            player->Move(-10);
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
    {
        if (player->GetRect()->y <= HEIGHT - player->GetRect()->h)
            player->Move(10);
    }
}

void Update(float)
{
    if (ball->GetRect()->y + ball->GetRect()->h > HEIGHT || ball->GetRect()->y < 0)
    {
        ball->SetVelY(-ball->GetVelY());
    }
    if (ball->GetRect()->x + ball->GetRect()->w > WIDTH || ball->GetRect()->x < 0)
    {
        if (ball->GetRect()->x < WIDTH / 2)
            opponentScore++;
        else
            playerScore++;
        std::cout << "PLAYER: " << playerScore << std::endl << "OPPONENT: " << opponentScore << std::endl;
        //SCORE
        ball->ChangePosition(WIDTH / 2, HEIGHT /2);
        ball->SetVelX(-ball->GetVelX());
    }

    ball->Move();
}

void Render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, player->GetRect());
    SDL_RenderFillRect(renderer, opponent->GetRect());
    SDL_RenderFillRect(renderer, ball->GetRect());
    SDL_RenderPresent(renderer);
}

int main()
{
    if (!InitializeSDL())
    {
        std::cout << "Error opening SDL. Shutting down." << std::endl;
        return 1;
    }

    isRunning = true;
    int ticksLastFrame;
    while (isRunning)
    {
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
        float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
        deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
        ticksLastFrame = SDL_GetTicks();
        ProcessInput();
        Update(deltaTime);
        Render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
