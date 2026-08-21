#include <iostream>
#include "board.hpp"

int main()
{
	srand(time(0));
	Board game;

	while(not game.hasEnded()) {
		game.render();
		game.play();
		game.update();
	}

	std::cout << "Você venceu!" << std::endl;

	return 0;
}