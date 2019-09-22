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

void Piece::SideHelper(int index, bool clockwise, Piece::POSITIONS s[], int ss) {
	for (int j = 0; j < ss; j++)
		if (positions[index] == s[j]) {
			if (!clockwise)
				positions[index] = s[(j + 1) % ss];
			else {
				if ((j - 1) > 0)
					positions[index] = s[(j - 1) % ss];
				else
					positions[index] = s[(j - 1) % ss + ss];
			}
			break;
		}
}

void Piece::MoveSide(POSITIONS side, bool clockwise) {
	if (pieceType != centre)
		for (int i = 0; i < SIZE; i++)
			if (InSide(side))
				switch (side) {
				case Piece::top:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							SideHelper(i, clockwise, TOP.connected, size(TOP.connected));
					break;
				case Piece::bottom:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							SideHelper(i, clockwise, BOTTOM.connected, size(BOTTOM.connected));
					break;
				case Piece::left:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							SideHelper(i, clockwise, LEFT.connected, size(LEFT.connected));
					break;
				case Piece::right:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							SideHelper(i, clockwise, RIGHT.connected, size(RIGHT.connected));
					break;
				case Piece::front:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							SideHelper(i, clockwise, FRONT.connected, size(FRONT.connected));
					break;
				case Piece::back:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							SideHelper(i, clockwise, BACK.connected, size(BACK.connected));
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