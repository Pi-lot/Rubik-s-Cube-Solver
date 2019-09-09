#include "Piece.h"

Piece::~Piece() {
	delete[] positions;
	delete[] colours;
}

void Piece::MoveSide(POSITIONS side, bool clockwise) {

}

int Piece::GetSize() {
	return SIZE;
}

Piece::POSITIONS *Piece::GetPositions() {
	return positions;
}

Piece::COLOURS *Piece::GetColours() {
	return colours;
}
