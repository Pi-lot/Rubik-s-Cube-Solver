#include "Piece.h"

Piece::Piece() {
	TOP = { back, right, front, left };
	BOTTOM = { front, right, back, left };
	FRONT = { top, right, bottom, left };
	BACK = { top, left, bottom, right };
	LEFT = { top, front, bottom, back };
	RIGHT = { top, back, bottom, front };
}

Piece::Piece(Piece::TYPE type, Piece::COLOURS *colour) {
	TOP = { back, right, front, left };
	BOTTOM = { front, right, back, left };
	FRONT = { top, right, bottom, left };
	BACK = { top, left, bottom, right };
	LEFT = { top, front, bottom, back };
	RIGHT = { top, back, bottom, front };

	pieceType = type;
	switch (type) {
	case Piece::edge:
		SIZE = 2;
		colours = new COLOURS[SIZE];
		positions = new POSITIONS[SIZE];
		break;
	case Piece::corner:
		SIZE = 3;
		colours = new COLOURS[SIZE];
		positions = new POSITIONS[SIZE];
		break;
	default:
		SIZE = 1;
		colours = new COLOURS;
		positions = new POSITIONS;
		break;
	}

	copy(colour, colour + SIZE, colours);
	for (int i = 0; i < SIZE; i++) {
		positions[i] = (POSITIONS)colours[i];
	}
}

Piece::~Piece() {
	//delete[] positions;
	//delete[] colours;
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
			switch (side) {
			case top:
				SideHelper(side, clockwise, TOP);
				break;
			case bottom:
				SideHelper(side, clockwise, BOTTOM);
				break;
			case left:
				SideHelper(side, clockwise, LEFT);
				break;
			case right:
				SideHelper(side, clockwise, RIGHT);
				break;
			case front:
				SideHelper(side, clockwise, FRONT);
				break;
			case back:
				SideHelper(side, clockwise, BACK);
				break;
			}
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
	for (int i = 0; i < SIZE; i++) {
		positions[i] = position[i];
	}
	delete[] position;
}

Piece::COLOURS *Piece::GetColours() {
	return colours;
}

char *Piece::ToChar() {
	return nullptr;
}

bool Piece::InSide(POSITIONS side) {
	for (int i = 0; i < SIZE; i++) {
		if (positions[i] == side)
			return true;
	}
	return false;
}