#include "./Game.h"
#include <iostream>

Game::Game()
{
    player = std::make_unique<Paddle>(30, HEIGHT / 2, 20, 100);
    opponent = std::make_unique<Paddle>(WIDTH - 60, HEIGHT / 2, 20, 100);
    ball = std::make_unique<Ball>(WIDTH / 2, HEIGHT /2, 15, 15);
    isRunning = false;
    playerScore = 0;
    opponentScore = 0;
}

bool Game::Initialize()
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

void Game::ProcessInput()
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        if (player->GetRect()->y >= 0)
            player->Move(-10);
    }
    if (state[SDL_SCANCODE_S])
    {
        if (player->GetRect()->y <= HEIGHT - player->GetRect()->h)
            player->Move(10);
    }

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    isRunning = false;
                if (event.key.keysym.sym == SDLK_r)
                {
                    ball->ChangePosition(WIDTH / 2 -1, HEIGHT /2 - 1);
                    ball->SetVelX(-ball->GetVelX());
                }
                break;
            default:
                break;
        }
    }
}

void Game::CollisionHandling()
{
    if ((ball->GetRect()->x == (player->GetRect()->x + player->GetRect()->w)) &&
        (ball->GetRect()->y + ball->GetRect()->h >= player->GetRect()->y) &&
        (ball->GetRect()->y <= player->GetRect()->y + player->GetRect()->h))
    {
        ball->SetVelX(-ball->GetVelX());
    }

    if ((ball->GetRect()->x + ball->GetRect()->w == opponent->GetRect()->x) &&
        (ball->GetRect()->y + ball->GetRect()->h >= opponent->GetRect()->y) &&
        (ball->GetRect()->y <= opponent->GetRect()->y + opponent->GetRect()->h)) {
        ball->SetVelX(-ball->GetVelX());
    }

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
        ball->ChangePosition(WIDTH / 2, HEIGHT /2);
        ball->SetVelX(-ball->GetVelX());
    }
}

void Game::OpponentAI()
{
    if (ball->GetVelY() < 0)
    {
        if (opponent->GetRect()->y >= 0)
            opponent->Move(-5);
    }
    else
    {
        if (opponent->GetRect()->y <= HEIGHT - opponent->GetRect()->h)
            opponent->Move(5);
    }
}

void Game::Run()
{
    isRunning = true;
    while (isRunning)
    {
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
        float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
        deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
        ticksLastFrame = SDL_GetTicks();
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Update()
{
    CollisionHandling();
    ball->Move();
    OpponentAI();
}

void Game::Render() const
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, player->GetRect());
    SDL_RenderFillRect(renderer, opponent->GetRect());
    SDL_RenderFillRect(renderer, ball->GetRect());

    SDL_RenderPresent(renderer);
}

void Game::Clear() const
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
