class Tile {
	int position, snake, ladder;

public:

	Tile() {}

	Tile(int p, int s, int l) {
		position = p;
		snake = s;
		ladder = l;
	}

	int getSnake() {
		return snake;
	}
	int getLadder() {
		return ladder;
	}
};