#include "Cube.h"

Cube::Cube() {
	pieces = new Piece[no];
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
	delete[] pieces;
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
	Piece::POSITIONS *positions = new Piece::POSITIONS[NOPOSITIONS];
	int index = 0;
	for (int i = 0; i < no; i++) {
		for (int j = 0; j < pieces[i].GetSize(); j++) {
			positions[index] = pieces[i].GetPositions()[j];
		}
	}
	return positions;
}

string Cube::CubeString() {
	string cubeString;
	string t;
	char toUse[NOPOSITIONS] {};
	char piecesChar[NOPOSITIONS] {};
	for (int i = 0; i < NOPOSITIONS; i++) {
		piecesChar[i] = NULL;
		toUse[i] = NULL;
	}
	int index = 0;
	for (int i = 0; i < no; i++) {
		for (int j = 0; j < pieces[i].GetSize(); j++) {
			toUse[index] = pieces[i].GetColours()[j];
			index++;
		}
	}
	for (int i = 0; i < NOPOSITIONS; i++) {
		if (i % 9 == 4) {
			index = 0;
			for (int j = 0; j < no; j++) {
				if (pieces[j].GetType() == Piece::centre && toUse[index] != NULL) {
					piecesChar[i] = toUse[index];
					t += toUse[index];
					toUse[index] = NULL;
					break;
				}
				index += pieces[j].GetSize();
			}
			continue;
		}
		index = 6;
		for (int j = 6; j < no; j++) {
			for (int k = 0; k < pieces[j].GetSize(); k++) {
				int centre;
				if (i % 9 < 4)
					centre = i + (4 - (i % 9));
				else
					centre = i - ((i % 9) - 4);
				if (pieces[j].GetPositions()[k] == piecesChar[centre] && toUse[index] != NULL) {
					t += toUse[index];
					toUse[index] = NULL;
				}
				index++;
			}
		}
	}
	cout << t << endl;
	return t;
}
