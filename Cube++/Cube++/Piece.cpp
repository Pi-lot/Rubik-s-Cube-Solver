#include "Piece.h"

void Piece::RotateAroundSide(Cube::Positions side, bool clockwise) {
}

bool Piece::InSide(Cube::Positions side) {
	return false;
}

Cube::PieceTypes Piece::GetPieceType() {
	return Cube::PieceTypes();
}

Cube::Colours* Piece::GetColours() {
	return nullptr;
}

Cube::Positions* Piece::GetPositions() {
	return nullptr;
}

void Piece::SetPositions(Cube(Positions[])) {
}

std::string Piece::GetColourString(Cube::Positions pos) {
	return std::string();
}
