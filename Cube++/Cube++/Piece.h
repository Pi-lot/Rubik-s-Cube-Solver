#pragma once
#include <array>

using namespace std;

class Piece {
public:
	const enum POSITIONS : char { top = 'g', bottom = 'b', left = 'o', right = 'r', front = 'y', back = 'w' };
	const enum COLOURS : char { green = 'g', blue = 'b', orange = 'o', red = 'r', yellow = 'y', white = 'w' };
	const enum TYPE : char { centre, edge, corner };
	Piece();
	Piece(Piece::TYPE type, Piece::COLOURS *colours);
	~Piece();
	void MoveSide(POSITIONS side, bool clockwise);
	int GetSize();
	TYPE GetType();
	POSITIONS *GetPositions();
	void SetPositions(POSITIONS *position);
	COLOURS *GetColours();
	struct CONNECTED {
		POSITIONS connected[4];
	} TOP = { back, right, front, left },
	BOTTOM = { front, right, back, left },
	FRONT = { top, right, bottom, left },
	BACK = { top, left, bottom, right },
	LEFT = { top, front, bottom, back },
	RIGHT = { top, back, bottom, front };
protected:
	TYPE pieceType;
	int SIZE;
	POSITIONS *positions;
	COLOURS *colours;
private:
	bool InSide(POSITIONS side);
	void SideHelper(Piece::POSITIONS side, bool clockwise, Piece::CONNECTED s);
};