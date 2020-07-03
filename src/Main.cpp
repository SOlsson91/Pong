#include "./Game.h"
#include "./GameState.h"

int main()
{
    Game game;
    if (!game.Initialize())
    {
        std::cerr << "Error opening SDL. Shutting down." << std::endl;
        return 1;
    }

    game.Run();
    game.Clear();
}
