#include "Cube.h"

Cube::Cube() {
	pieces = new Piece[no] {};
	char chars[] { 'g', 'b', 'o', 'r', 'y', 'w' };
	for (int i = 0; i < 6; i++) {
		pieces[i] = Centre(Piece::COLOURS(chars[i]));
	}
	Piece::COLOURS *c = new Piece::COLOURS[2];
	c[0] = Piece::green;
	c[1] = Piece::yellow;
	pieces[6] = Piece(Piece::edge, c);
	c[0] = Piece::green;
	c[1] = Piece::white;
	pieces[7] = Piece(Piece::edge, c);
	c[0] = Piece::green;
	c[1] = Piece::red;
	pieces[8] = Piece(Piece::edge, c);
	c[0] = Piece::green;
	c[1] = Piece::orange;
	pieces[9] = Piece(Piece::edge, c);
	c[0] = Piece::blue;
	c[1] = Piece::yellow;
	pieces[10] = Piece(Piece::edge, c);
	c[0] = Piece::blue;
	c[1] = Piece::white;
	pieces[11] = Piece(Piece::edge, c);
	c[0] = Piece::blue;
	c[1] = Piece::red;
	pieces[12] = Piece(Piece::edge, c);
	c[0] = Piece::blue;
	c[1] = Piece::orange;
	pieces[13] = Piece(Piece::edge, c);
	c[0] = Piece::yellow;
	c[1] = Piece::red;
	pieces[14] = Piece(Piece::edge, c);
	c[0] = Piece::orange;
	c[1] = Piece::yellow;
	pieces[15] = Piece(Piece::edge, c);
	c[0] = Piece::orange;
	c[1] = Piece::white;
	pieces[16] = Piece(Piece::edge, c);
	c[0] = Piece::white;
	c[1] = Piece::red;
	pieces[17] = Piece(Piece::edge, c);
	delete[] c;
	Piece::COLOURS *ct = new Piece::COLOURS[3];
	ct[0] = Piece::green;
	ct[1] = Piece::yellow;
	ct[2] = Piece::red;
	pieces[18] = Piece(Piece::corner, ct);
	ct[0] = Piece::green;
	ct[1] = Piece::yellow;
	ct[2] = Piece::orange;
	pieces[19] = Piece(Piece::corner, ct);
	ct[0] = Piece::green;
	ct[1] = Piece::white;
	ct[2] = Piece::red;
	pieces[20] = Piece(Piece::corner, ct);
	ct[0] = Piece::green;
	ct[1] = Piece::white;
	ct[2] = Piece::orange;
	pieces[21] = Piece(Piece::corner, ct);
	ct[0] = Piece::blue;
	ct[1] = Piece::yellow;
	ct[2] = Piece::orange;
	pieces[22] = Piece(Piece::corner, ct);
	ct[0] = Piece::blue;
	ct[1] = Piece::yellow;
	ct[2] = Piece::red;
	pieces[23] = Piece(Piece::corner, ct);
	ct[0] = Piece::blue;
	ct[1] = Piece::white;
	ct[2] = Piece::red;
	pieces[24] = Piece(Piece::corner, ct);
	ct[0] = Piece::blue;
	ct[1] = Piece::white;
	ct[2] = Piece::orange;
	pieces[25] = Piece(Piece::corner, ct);
	delete[] ct;
}

Cube::~Cube() {
	//delete[] pieces;
}

void Cube::RotateSide(Piece::POSITIONS side, bool clockwise) {
	for (int i = 0; i < no; i++)
		pieces[i].MoveSide(side, clockwise);
}

void Cube::SetPositions(Piece::POSITIONS *positions) {
	Piece::POSITIONS *pos = new Piece::POSITIONS;
	int index = 0;
	for (int i = 0; i < 6; i++) {
		pos = new Piece::POSITIONS;
		pieces[i].SetPositions(pos);
		index++;
	}
	for (int i = index; i < no; i += (pieces[index].GetSize())) {
		pos = new Piece::POSITIONS[pieces[index].GetSize()];
		for (int j = 0; j < (pieces[index].GetSize()); j++)
			pos[j] = positions[i + j];
		pieces[index].SetPositions(pos);
		index++;
	}
	delete[] pos;
	delete[] positions;
}

bool Cube::IsSolved() {
	bool solved = true;
	for (int i = 0; i < no; i++)
		for (int j = 0; j < pieces[i].GetSize(); j++)
			if (pieces[i].GetPositions()[j] != pieces[i].GetColours()[j])
				solved = false;
	return solved;
}

void Cube::PrintColours() {
	for (int i = 0; i < no; i++)
		for (int j = 0; j < pieces[i].GetSize(); j++)
			cout << pieces[i].GetColours()[j];
	cout << endl;
}

void Cube::PrintPositions() {
	for (int i = 0; i < no; i++)
		for (int j = 0; j < pieces[i].GetSize(); j++)
			cout << pieces[i].GetPositions()[j];
	cout << endl;
}

Piece::POSITIONS *Cube::GetPositions() {
	Piece::POSITIONS *positions = new Piece::POSITIONS[NOPOSITIONS] {};
	int index = 0;
	for (int i = 0; i < no; i++) {
		for (int j = 0; j < pieces[i].GetSize(); j++) {
			positions[index] = pieces[i].GetPositions()[j];
		}
	}
	return positions;
}

int Cube::GetIndexEdge(Piece::POSITIONS pos, Piece::CONNECTED side, int centre) {
	for (int z = 0; z < size(side.connected); z++)
		if (side.connected[z] == pos)
			switch (z) {
			case 0:
				return centre - 3;
			case 1:
				return centre - 1;
			case 2:
				return centre + 1;
			case 3:
				return centre + 3;
			}
}

int Cube::GetIndexCorner(Piece piece, Piece::POSITIONS pos, Piece::CONNECTED side, int centre) {
	int s = piece.GetSize();
	Piece::POSITIONS *others = new Piece::POSITIONS[s - 1] {};
	int index = 0;
	for (int i = 0; i < piece.GetSize(); i++)
		if (piece.GetPositions()[i] != pos) {
			others[index] = piece.GetPositions()[i];
			index++;
		}
	for (int i = 0; i < size(side.connected); i++) {
		for (int j = 0; j < s; j++) {
			if (others[j] == side.connected[i] && (others[(j + 1) % 2] == side.connected[(i + 1) % size(side.connected)])) {
				switch (i) {
				case 0:
					delete[] others;
					return centre - 2;
					break;
				case 1:
					delete[] others;
					return centre + 4;
					break;
				case 2:
					delete[] others;
					return centre + 2;
					break;
				case 3:
					delete[] others;
					return centre - 4;
					break;
				}
			}
		}
	}
}

char *Cube::CubeString() {
	char *colour = new char[NOPOSITIONS] {};
	char position[NOPOSITIONS] {};
	for (int i = 0; i < no; i++) {
		if (pieces[i].GetType() == Piece::centre) {
			for (int j = 4; j < NOPOSITIONS; j += 9)
				if (colour[j] == NULL) {
					colour[j] = pieces[i].GetColours()[0];
					position[j] = pieces[i].GetPositions()[0];
					break;
				}
		} else if (pieces[i].GetType() == Piece::edge) {
			for (int j = 4; j < NOPOSITIONS; j += 9)
				for (int k = 0; k < pieces[i].GetSize(); k++)
					if (pieces[i].GetPositions()[k] == position[j]) {
						int index;
						switch (pieces[i].GetPositions()[k]) {
						case Piece::top:
							if (k == 0)
								index = GetIndexEdge(pieces[i].GetPositions()[k + 1], pieces[i].TOP, j);
							else
								index = GetIndexEdge(pieces[i].GetPositions()[k - 1], pieces[i].TOP, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							break;
						case Piece::bottom:
							if (k == 0)
								index = GetIndexEdge(pieces[i].GetPositions()[k + 1], pieces[i].BOTTOM, j);
							else
								index = GetIndexEdge(pieces[i].GetPositions()[k - 1], pieces[i].BOTTOM, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							break;
						case Piece::left:
							if (k == 0)
								index = GetIndexEdge(pieces[i].GetPositions()[k + 1], pieces[i].LEFT, j);
							else
								index = GetIndexEdge(pieces[i].GetPositions()[k - 1], pieces[i].LEFT, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							break;
						case Piece::right:
							if (k == 0)
								index = GetIndexEdge(pieces[i].GetPositions()[k + 1], pieces[i].RIGHT, j);
							else
								index = GetIndexEdge(pieces[i].GetPositions()[k - 1], pieces[i].RIGHT, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							break;
						case Piece::front:
							if (k == 0)
								index = GetIndexEdge(pieces[i].GetPositions()[k + 1], pieces[i].FRONT, j);
							else
								index = GetIndexEdge(pieces[i].GetPositions()[k - 1], pieces[i].FRONT, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							break;
						case Piece::back:
							if (k == 0)
								index = GetIndexEdge(pieces[i].GetPositions()[k + 1], pieces[i].BACK, j);
							else
								index = GetIndexEdge(pieces[i].GetPositions()[k - 1], pieces[i].BACK, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							break;
						}
						break;
					}
		} else if (pieces[i].GetType() == Piece::corner) {
			for (int j = 4; j < NOPOSITIONS; j += 9) {
				for (int k = 0; k < pieces[i].GetSize(); k++) {
					//cout << pieces[i].GetPositions()[k]<< i << "," << position[j] << " " << j << " ";
					if (pieces[i].GetPositions()[k] == position[j]) {
						//cout << "True ";
						int index;
						switch (pieces[i].GetPositions()[k]) {
						case Piece::top:
							index = GetIndexCorner(pieces[i], pieces[i].GetPositions()[k], pieces[i].TOP, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							//cout << index << "|" << position[index] << "|" << j << " ";
							break;
						case Piece::bottom:
							index = GetIndexCorner(pieces[i], pieces[i].GetPositions()[k], pieces[i].BOTTOM, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							//cout << index << "|" << position[index] << "|" << j << " ";
							break;
						case Piece::left:
							index = GetIndexCorner(pieces[i], pieces[i].GetPositions()[k], pieces[i].LEFT, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							//cout << index << "|" << position[index] << "|" << j << " ";
							break;
						case Piece::right:
							index = GetIndexCorner(pieces[i], pieces[i].GetPositions()[k], pieces[i].RIGHT, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							//cout << index << "|" << position[index] << "|" << j << " ";
							break;
						case Piece::front:
							index = GetIndexCorner(pieces[i], pieces[i].GetPositions()[k], pieces[i].FRONT, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							//cout << index << "|" << position[index] << "|" << j << " ";
							break;
						case Piece::back:
							index = GetIndexCorner(pieces[i], pieces[i].GetPositions()[k], pieces[i].BACK, j);
							position[index] = pieces[i].GetPositions()[k];
							colour[index] = pieces[i].GetColours()[k];
							//cout << index << "|" << position[index] << "|" << j << " ";
							break;
						}
						break;
					}
					//cout << endl;
				}
			}
		}
	}
	cout << "CubeString returning:";
	for (int i = 0; i < NOPOSITIONS; i++)
		cout << colour[i];
	cout << endl;
	return colour;
}
