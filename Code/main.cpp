#include "Game/Game.h"
#include "Tools/Time.h"

int main()
{
	Game& game = Game::GetInstance();

	try
	{
		while (game.IsRunning())
		{
			game.HandleInput();
			game.Update(Time::DeltaTime());
			game.Render();
		}
	}
	catch (const std::exception& error)
	{
		game.HandleException(error);
	}

	return 0;
}