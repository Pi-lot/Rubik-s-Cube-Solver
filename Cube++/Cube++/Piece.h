#pragma once
#include <array>

using namespace std;

class Piece {
public:
	const enum POSITIONS { top, bottom, left, right, front, back };
	const enum COLOURS { green, blue, yellow, white, red, orange };
	~Piece();
	void MoveSide(POSITIONS side, bool clockwise);
	int GetSize();
	POSITIONS *GetPositions();
	COLOURS *GetColours();
protected:
	int SIZE;
	POSITIONS *positions;
	COLOURS *colours;
};

