#include "Cube.h"

Cube::Cube() {
	pieces = new Piece[no];
	char chars[]{ 'g', 'b', 'o', 'r', 'g', 'w' };
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
	solved = new Piece::POSITIONS[54];
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

Piece::POSITIONS *Cube::GetPositions() {
	Piece::POSITIONS *positions = new Piece::POSITIONS[54];
	int index = 0;
	cout << "--------------------------" << endl;
	cout << "GetPositions" << endl;
	cout << "--------------------------" << endl;
	//Piece::POSITIONS *positions = GetPositions();
	//copy(positions, positions + 54, solved);
	//for (int i = 0; i < 54; i++) {
		//cout << positions[i] << ",";
	//}
	for (int i = 0; i < no; i++) {
		Piece::POSITIONS *pos = new Piece::POSITIONS[pieces->GetSize()];
		copy(pieces[i].GetPositions(), pieces[i].GetPositions() + pieces[i].GetSize(), pos);
		for (int j = 0; j < pieces[i].GetSize(); j++) {
			positions[index] = pos[j];
			cout << "|" << positions[index] << "|";
		}
		cout << endl;
	}
	cout << "--------------------------" << endl;
	return positions;
}

string *Cube::CubeString() {
	return nullptr;
}
