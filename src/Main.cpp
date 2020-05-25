#include "./Game.h"

int main()
{
    Game game;
    if (!game.Initialize())
    {
        std::cout << "Error opening SDL. Shutting down." << std::endl;
        return 1;
    }

    game.Run();
    game.Clear();
}
