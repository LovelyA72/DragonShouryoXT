#pragma once
class Move {
public:
	Move(int t, int a, int b) {
		type = t;
		move[0] = a;
		move[1] = b;
	}
	Move() {
	}
	int type = 0;
	int move[2] = { 0,0 };
};