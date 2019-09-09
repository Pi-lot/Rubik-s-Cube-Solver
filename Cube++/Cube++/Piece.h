#pragma once
#include <array>

using namespace std;

class Piece {
public:
	const enum POSITIONS { top, bottom, left, right, front, back };
	const enum COLOURS { green, blue, yellow, white, red, orange };
	const enum TYPE { centre, edge, corner };
	Piece();
	~Piece();
	void MoveSide(POSITIONS side, bool clockwise);
	int GetSize();
	POSITIONS *GetPositions();
	COLOURS *GetColours();
protected:
	TYPE pieceType;
	int SIZE;
	POSITIONS *positions;
	COLOURS *colours;
private:
	bool InSide(POSITIONS side);
	void SideHelper(int index, bool clockwise, Piece::POSITIONS s[], int ss);
	struct CONNECTED {
		POSITIONS connected[4];
	} TOP, BOTTOM, RIGHT, LEFT, FRONT, BACK;
};

