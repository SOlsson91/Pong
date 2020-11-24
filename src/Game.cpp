#include "./Game.h"

Game::Game()
    : m_IsRunning(false), m_PlayerScore(0), m_OpponentScore(0)
{
    m_Player = std::make_unique<Paddle>(30, HEIGHT / 2, PADDLEWIDTH, PADDLEHEIGHT);
    m_Opponent = std::make_unique<Paddle>(WIDTH - 60, HEIGHT / 2, PADDLEWIDTH, PADDLEHEIGHT);
    m_Ball = std::make_unique<Ball>(WIDTH / 2, HEIGHT /2, BALLSIZE, BALLSIZE);
}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING == 0))
    {
        std::cerr << "Error Initializing SDL" << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "Error loading TTF" << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_BORDERLESS);
    if (!m_Window)
    {
        std::cerr << "Error creating SDL Window." << std::endl;
        return false;
    }

    const int driverIndex = -1;
    m_Renderer = SDL_CreateRenderer(m_Window, driverIndex, SDL_RENDERER_ACCELERATED);
    if (!m_Renderer)
    {
        std::cerr << "Error creating SDL Renderer." << std::endl;
        return false;
    }

    const int fontSize = 50;
    m_Font = TTF_OpenFont("./fonts/libel-suit.ttf", fontSize);
    if (m_Font == nullptr)
    {
        std::cerr << "Error loing font" << std::endl;
        return false;
    }
    m_TextColor = { 255, 255, 255, 255 };
    return true;
}

void Game::ProcessInput()
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        if (m_Player->GetRect()->y >= 0)
            m_Player->Move(-10);
    }
    if (state[SDL_SCANCODE_S])
    {
        if (m_Player->GetRect()->y <= HEIGHT - m_Player->GetRect()->h)
            m_Player->Move(10);
    }

    while (SDL_PollEvent(&m_Event) != 0)
    {
        switch (m_Event.type)
        {
            case SDL_QUIT:
                m_IsRunning = false;
                break;
            case SDL_KEYDOWN:
                if (m_Event.key.keysym.sym == SDLK_ESCAPE)
                    m_IsRunning = false;
                if (m_Event.key.keysym.sym == SDLK_r)
                {
                    m_Ball->ChangePosition(WIDTH / 2 -1, HEIGHT /2 - 1);
                    m_Ball->SetVelX(-m_Ball->GetVelX());
                }
                break;
            default:
                break;
        }
    }
}

void Game::CollisionHandling()
{
    if ((m_Ball->GetRect()->x == (m_Player->GetRect()->x + m_Player->GetRect()->w)) &&
        (m_Ball->GetRect()->y + m_Ball->GetRect()->h >= m_Player->GetRect()->y) &&
        (m_Ball->GetRect()->y <= m_Player->GetRect()->y + m_Player->GetRect()->h))
    {
        m_Ball->SetVelX(-m_Ball->GetVelX());
    }

    if ((m_Ball->GetRect()->x + m_Ball->GetRect()->w == m_Opponent->GetRect()->x) &&
        (m_Ball->GetRect()->y + m_Ball->GetRect()->h >= m_Opponent->GetRect()->y) &&
        (m_Ball->GetRect()->y <= m_Opponent->GetRect()->y + m_Opponent->GetRect()->h))
	{
        m_Ball->SetVelX(-m_Ball->GetVelX());
    }

    if (m_Ball->GetRect()->y + m_Ball->GetRect()->h > HEIGHT || m_Ball->GetRect()->y < 0)
    {
        m_Ball->SetVelY(-m_Ball->GetVelY());
    }

    if (m_Ball->GetRect()->x + m_Ball->GetRect()->w > WIDTH || m_Ball->GetRect()->x < 0)
    {
        if (m_Ball->GetRect()->x < WIDTH / 2)
            m_OpponentScore++;
        else
            m_PlayerScore++;
        std::cout << "PLAYER: " << m_PlayerScore << std::endl << "OPPONENT: " << m_OpponentScore << std::endl;
        m_Ball->ChangePosition(WIDTH / 2, HEIGHT /2);
        m_Ball->SetVelX(-m_Ball->GetVelX());
    }
}

void Game::OpponentAI()
{
    if (m_Ball->GetVelY() < 0)
    {
        if (m_Opponent->GetRect()->y >= 0)
            m_Opponent->Move(-5);
    }
    else
    {
        if (m_Opponent->GetRect()->y <= HEIGHT - m_Opponent->GetRect()->h)
            m_Opponent->Move(5);
    }
}

void Game::Run()
{
    m_IsRunning = true;
    while (m_IsRunning)
    {
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksLastFrame + FRAME_TARGET_TIME));
        float deltaTime = (SDL_GetTicks() - m_TicksLastFrame) / 1000.0f;
        deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
        m_TicksLastFrame = SDL_GetTicks();
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Update()
{
    CollisionHandling();
    m_Ball->Move();
    OpponentAI();
}

void Game::RenderText(std::string text, int posX, int posY)
{
    SDL_Rect rect;
    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, text.c_str(), m_TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture( texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = posX;
    rect.y = posY;
    SDL_RenderCopy(m_Renderer, texture, nullptr, &rect);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 21, 21, 21, 255);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_Renderer, m_Player->GetRect());
    SDL_RenderFillRect(m_Renderer, m_Opponent->GetRect());
    SDL_RenderFillRect(m_Renderer, m_Ball->GetRect());

    RenderText(std::to_string(m_PlayerScore), WIDTH / 2 - 40, 20);
    RenderText(std::to_string(m_OpponentScore), WIDTH / 2 + 40, 20);

    SDL_RenderPresent(m_Renderer);
}

void Game::Clear() const
{
    TTF_CloseFont(m_Font);
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    TTF_Quit();
    SDL_Quit();
}
