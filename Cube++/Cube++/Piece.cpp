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

void Piece::MoveSide(POSITIONS side, bool clockwise) {
	if (pieceType != centre)
		for (int i = 0; i < SIZE; i++)
			if (InSide(side))
				switch (side) {
				case Piece::top:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							for (int j = 0; j < size(TOP.connected); j++)
								if (positions[i] == TOP.connected[j]) {
									if (clockwise)
										positions[i] == TOP.connected[(j++) % size(TOP.connected)];
									else {
										if (j-- > 0)
											positions[i] == TOP.connected[(j--) % size(TOP.connected)];
										else
											positions[i] == TOP.connected[(j--) % size(TOP.connected) +
											size(TOP.connected)];
									}
								}
					break;
				case Piece::bottom:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							for (int j = 0; j < size(BOTTOM.connected); j++)
								if (positions[i] == BOTTOM.connected[j]) {
									if (clockwise)
										positions[i] == BOTTOM.connected[(j++) % size(BOTTOM.connected)];
									else {
										if (j-- > 0)
											positions[i] == BOTTOM.connected[(j--) % size(BOTTOM.connected)];
										else
											positions[i] == BOTTOM.connected[(j--) % size(BOTTOM.connected) +
											size(BOTTOM.connected)];
									}
								}
					break;
				case Piece::left:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							for (int j = 0; j < size(LEFT.connected); j++)
								if (positions[i] == LEFT.connected[j]) {
									if (clockwise)
										positions[i] == LEFT.connected[(j++) % size(LEFT.connected)];
									else {
										if (j-- > 0)
											positions[i] == LEFT.connected[(j--) % size(LEFT.connected)];
										else
											positions[i] == LEFT.connected[(j--) % size(LEFT.connected) +
											size(LEFT.connected)];
									}
								}
					break;
				case Piece::right:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							for (int j = 0; j < size(RIGHT.connected); j++)
								if (positions[i] == RIGHT.connected[j]) {
									if (clockwise)
										positions[i] == RIGHT.connected[(j++) % size(RIGHT.connected)];
									else {
										if (j-- > 0)
											positions[i] == RIGHT.connected[(j--) % size(RIGHT.connected)];
										else
											positions[i] == RIGHT.connected[(j--) % size(RIGHT.connected) +
											size(RIGHT.connected)];
									}
								}
					break;
				case Piece::front:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							for (int j = 0; j < size(FRONT.connected); j++)
								if (positions[i] == FRONT.connected[j]) {
									if (clockwise)
										positions[i] == FRONT.connected[(j++) % size(FRONT.connected)];
									else {
										if (j-- > 0)
											positions[i] == FRONT.connected[(j--) % size(FRONT.connected)];
										else
											positions[i] == FRONT.connected[(j--) % size(FRONT.connected) +
											size(FRONT.connected)];
									}
								}
					break;
				case Piece::back:
					for (int i = 0; i < SIZE; i++)
						if (positions[i] != side)
							for (int j = 0; j < size(BACK.connected); j++)
								if (positions[i] == BACK.connected[j]) {
									if (clockwise)
										positions[i] == BACK.connected[(j++) % size(BACK.connected)];
									else {
										if (j-- > 0)
											positions[i] == BACK.connected[(j--) % size(BACK.connected)];
										else
											positions[i] == BACK.connected[(j--) % size(BACK.connected) +
											size(BACK.connected)];
									}
								}
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
