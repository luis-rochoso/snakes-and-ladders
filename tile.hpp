class Tile {
	int position, snake, ladder;

public:

	Tile(int p, int s, int l) {
		position = p;
		snake = s;
		ladder = l;
	}

	bool hasSnake() {
		return p != s;
	}
	bool hasLadder() {
		return p != l;
	}
};