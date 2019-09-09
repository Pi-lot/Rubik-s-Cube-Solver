#include "Piece.h"

Piece::Piece() {
	TOP = { back, right, front, left };
	BOTTOM = { back, left, front, right };
	FRONT = { top, right, bottom, left };
	BACK = { top, left, bottom, right };
	LEFT = { top, front, bottom, back };
	RIGHT = { top, back, bottom, front };
}

Piece::~Piece() {
	delete[] positions;
	delete[] colours;
}

void Piece::SideHelper(int index, bool clockwise, Piece::POSITIONS s[], int ss) {
	for (int j = 0; j < ss; j++)
		if (positions[index] == s[j]) {
			if (clockwise)
				positions[index] == s[(j++) % ss];
			else {
				if (j-- > 0)
					positions[index] == s[(j--) % ss];
				else
					positions[index] == s[(j--) % ss + ss];
			}
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
				default:
					break;
				}
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

bool Piece::InSide(POSITIONS side) {
	for (int i = 0; i < SIZE; i++) {
		if (positions[i] == side)
			return true;
	}
	return false;
}
