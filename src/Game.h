#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <string>

#include "./Paddle.h"
#include "./Ball.h"

class Game
{
private:
    const unsigned int FPS = 60;
    const unsigned int FRAME_TARGET_TIME = 1000.0f / FPS;
    const int WIDTH = 1280;
    const int HEIGHT = 720;
    const int PADDLEWIDTH = 20;
    const int PADDLEHEIGHT = 100;
    const int BALLSIZE = 15;

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Event m_Event;
    TTF_Font* m_Font;
    SDL_Color m_TextColor;

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
    void Render();
    void Clear() const;
    void RenderText(std::string text, int x, int y);
};
