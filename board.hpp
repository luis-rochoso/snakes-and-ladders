#include "tile.hpp"

class Board {
	int playerPosition = 0;
	Tile boardTiles[101];

public:
    void move();
	void slide();
	void climb();

	Board() {
		for (int i = 0; i < 101; ++i) {
			switch (i) {

			case 1:
				boardTiles[i] = Tile(i, i, 38);
				break;

			case 4:
				boardTiles[i] = Tile(i+1, i+1, 14);
				break;

			case 9:
				boardTiles[i] = Tile(i, i, 31);
				break;

			case 16:
				boardTiles[i] = Tile(i, 6, i);
				break;

			case 21:
				boardTiles[i] = Tile(i, i, 42);
				break;

			case 28:
				boardTiles[i] = Tile(i, i, 84);
				break;

			case 36:
				boardTiles[i] = Tile(i, i, 44);
				break;

			case 47:
				boardTiles[i] = Tile(i, 26, i);
				break;

			case 49:
				boardTiles[i] = Tile(i, 11, i);
				break;

			case 51:
				boardTiles[i] = Tile(i, i, 67);
				break;

			case 56:
				boardTiles[i] = Tile(i, 53, i);
				break;

			case 62:
				boardTiles[i] = Tile(i, 19, i);
				break;

			case 64:
				boardTiles[i] = Tile(i, 60, i);
				break;

			case 71:
				boardTiles[i] = Tile(i, i, 91);
				break;

			case 80:
				boardTiles[i] = Tile(i, i, 100);
				break;

			case 87:
				boardTiles[i] = Tile(i, 24, i);
				break;

			case 93:
				boardTiles[i] = Tile(i, 73, i);
				break;

			case 95:
				boardTiles[i] = Tile(i, 75, i);
				break;

			case 98:
				boardTiles[i] = Tile(i, 78, i);
				break;
			
			default:
				boardTiles[i] = Tile(i, i, i);
				break;
			}
		}
	}
}