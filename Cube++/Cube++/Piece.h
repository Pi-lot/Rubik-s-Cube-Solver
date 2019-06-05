#pragma once
#include "Cube.h"
#include <string>

class Piece {
protected: Cube::Positions* positions;
		   Cube::PieceTypes pieceType;
		   Cube::Colours* colours;
public:
	void RotateAroundSide(Cube::Positions side, bool clockwise);
	bool InSide(Cube::Positions side);
	Cube::PieceTypes GetPieceType();
	Cube::Colours* GetColours();
	Cube::Positions* GetPositions();
	void SetPositions(Cube(Positions[]));
	std::string GetColourString(Cube::Positions pos);
};
