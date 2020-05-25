#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

#include "./Paddle.h"
#include "./Ball.h"

class Game
{
private:
    const unsigned int FPS = 60;
    const unsigned int FRAME_TARGET_TIME = 1000.0f / FPS;
    const int WIDTH = 1280;
    const int HEIGHT = 720;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    std::unique_ptr<Paddle> player;
    std::unique_ptr<Paddle> opponent;
    std::unique_ptr<Ball> ball;

    bool isRunning;
    int playerScore;
    int opponentScore;
    int ticksLastFrame;
public:
    Game();
    bool Initialize();
    void ProcessInput();
    void CollisionHandling();
    void OpponentAI();
    void Run();
    void Update();
    void Render() const;
    void Clear() const;
};
