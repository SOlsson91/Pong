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

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Event m_Event;

    std::unique_ptr<Paddle> m_Player;
    std::unique_ptr<Paddle> m_Opponent;
    std::unique_ptr<Ball> m_Ball;

    bool m_IsRunning;
    int m_PlayerScore;
    int m_OpponentScore;
    int m_TicksLastFrame;
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
