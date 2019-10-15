#include "Piece.h"

Piece::Piece() {
}

Piece::Piece(Piece::TYPE type, Piece::COLOURS *colour) {
	pieceType = type;
	switch (type) {
	case Piece::edge:
		SIZE = 2;
		colours = new COLOURS[SIZE] {};
		positions = new POSITIONS[SIZE] {};
		break;
	case Piece::corner:
		SIZE = 3;
		colours = new COLOURS[SIZE] {};
		positions = new POSITIONS[SIZE] {};
		break;
	default:
		SIZE = 1;
		colours = new COLOURS {};
		positions = new POSITIONS {};
		break;
	}

	copy(colour, colour + SIZE, colours);
	for (int i = 0; i < SIZE; i++) {
		positions[i] = (POSITIONS)colours[i];
	}
}

Piece::~Piece() {
	//delete[] positions, colours;
}

void Piece::SideHelper(Piece::POSITIONS side, bool clockwise, Piece::CONNECTED s) {
	for (int i = 0; i < SIZE; i++) {
		if (positions[i] != side)
			for (int j = 0; j < size(s.connected); j++)
				if (positions[i] == s.connected[j]) {
					int nextIndex = j;
					if (clockwise)
						nextIndex++;
					else
						nextIndex--;
					while (nextIndex < 0)
						nextIndex += size(s.connected);
					nextIndex %= size(s.connected);
					positions[i] = s.connected[nextIndex];
					break;
				}
	}
}

void Piece::MoveSide(POSITIONS side, bool clockwise) {
	if (pieceType != centre)
		if (InSide(side))
			SideHelper(side, clockwise, GetConnectedSide(side));
}

int Piece::GetSize() {
	return SIZE;
}

Piece::TYPE Piece::GetType() {
	return pieceType;
}

Piece::POSITIONS *Piece::GetPositions() {
	return positions;
}

void Piece::SetPositions(POSITIONS *position) {
	copy(position, position + SIZE, positions);
	delete[] position;
}

Piece::COLOURS *Piece::GetColours() {
	return colours;
}

Piece::CONNECTED Piece::GetConnectedSide(Piece::POSITIONS side) {
	switch (side) {
	case Piece::top:
		return TOP;
		break;
	case Piece::bottom:
		return BOTTOM;
		break;
	case Piece::left:
		return LEFT;
		break;
	case Piece::right:
		return RIGHT;
		break;
	case Piece::front:
		return FRONT;
		break;
	case Piece::back:
		return BACK;
		break;
	}
}

bool Piece::InSide(POSITIONS side) {
	for (int i = 0; i < SIZE; i++) {
		if (positions[i] == side)
			return true;
	}
	return false;
}