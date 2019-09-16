#pragma once
#include <iostream>
#include "Piece.h"
#include "Centre.h"

#define SIZE 3
#define NOPOSITIONS 54

class Cube {
private:
	Piece *pieces;
	int no = (SIZE * SIZE * SIZE) - ((SIZE - 2) * (SIZE - 2) * (SIZE - 2));
	Piece::POSITIONS *solved;
public:
	Cube();
	~Cube();
	void RotateSide(Piece::POSITIONS side, bool clockwise);
	void SetPositions(Piece::POSITIONS *positions);
	bool IsSolved();
	Piece::POSITIONS *GetPositions();
	string *CubeString();
};


