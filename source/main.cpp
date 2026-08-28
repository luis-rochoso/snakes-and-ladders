#include "board.hpp"
#include "raylib.h"

int main()
{
	Board game;
	game.init();

	while(!game.hasEnded() and !WindowShouldClose()) {
		game.render();
		game.play();
		if (game.hasPlayed()) {game.update();}
	}


	game.shutdown();

	return 0;
}