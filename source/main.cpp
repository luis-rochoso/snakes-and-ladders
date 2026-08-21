#include <iostream>
#include "board.hpp"
#include "raylib.h"

int main()
{
	srand(time(0));
	Board game;
	game.init();

	while(not game.hasEnded() and (not WindowShouldClose())) {
		game.render();
		game.play();
		game.update();
	}

	game.shutdown();
	std::cout << "Você venceu!" << std::endl;

	return 0;
}