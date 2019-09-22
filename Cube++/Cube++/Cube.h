#pragma once
#include "Piece.h"
#include "Centre.h"
#include <iostream>

#define SIZE 3
#define NOPOSITIONS 54

class Cube {
private:
	Piece *pieces;
	int no = (SIZE * SIZE * SIZE) - ((SIZE - 2) * (SIZE - 2) * (SIZE - 2));
public:
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


