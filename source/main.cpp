#include <iostream>
#include "board.hpp"
#include "raylib.h"

int main()
{
	srand(time(0));
	Board game;
	game.init();

	while(!game.hasEnded() and !WindowShouldClose()) {
		game.render();
		game.play();
		if (game.hasPlayed()) {game.update();}
	}

	
	game.shutdown();
	std::cout << "Você venceu!" << std::endl;

	return 0;
}