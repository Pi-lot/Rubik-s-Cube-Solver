#pragma once
#include "Piece.h"
#include "Centre.h"
#include <iostream>

class Cube {
private:
	Piece *pieces;
	int no = (SIZE * SIZE * SIZE) - ((SIZE - 2) * (SIZE - 2) * (SIZE - 2));
public:
	static const int SIZE = 3;
	static const int NOPOSITIONS = 54;
	Cube();
	~Cube();
	void RotateSide(Piece::POSITIONS side, bool clockwise);
	void SetPositions(Piece::POSITIONS *positions);
	bool IsSolved();
	void PrintColours();
	void PrintPositions();
	Piece::POSITIONS *GetPositions();
	string CubeString();
};


