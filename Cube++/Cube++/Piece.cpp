#include "Piece.h"

using namespace RubiksCube;

void Piece::RotateAroundSide(Cube::Positions side, bool clockwise) {
}

bool Piece::InSide(Cube::Positions side) {
	return false;
}

Cube::PieceTypes Piece::GetPieceType() {
	return Cube::PieceTypes();
}

Cube::Colours RubiksCube::Piece::GetColours() {
	return Cube::Colours();
}

Cube::Positions RubiksCube::Piece::GetPositions() {
	return Cube::Positions();
}

void Piece::SetPositions(Cube(Positions[])) {
}

std::string Piece::GetColourString(Cube::Positions pos) {
	return std::string();
}
