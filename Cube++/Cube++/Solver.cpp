#include "Solver.h"

Solver::Solver(Cube cube) {
	this->cube = cube;
	crossCentre = NULL;
}

void Solver::SetCube(Cube cube) {
	this->cube = cube;
}

int Solver::CheckCross(char side) {
	cout << "Checking if there is a cross in: " << side  << "... ";
	int cross = 0;
	Piece *pieces = cube.GetPieces();
	for (int i = 0; i < cube.GetNumPieces(); i++) {
		if (pieces[i].GetType() == Piece::edge) {
			for (int j = 0; j < pieces[i].GetSize(); j++) {
				if (pieces[i].GetPositions()[j] == pieces[i].GetColours()[j] && pieces[i].GetPositions()[j] == side) {
					cross++;
					if (pieces[i].GetPositions()[(j + 1) % pieces[i].GetSize()] == pieces[i].GetColours()[(j + 1) % pieces[i].GetSize()])
						cross++;
				}
			}
		}
	}
	cout << "Done. Returned: " << cross << endl;
	return cross;
}

bool Solver::CheckLayer(int no) {
	return false;
}

char Solver::BestCross() {
	cout << "Finding best Cross..." << endl;
	int best = 0;
	char bestSide = 0;
	for (int i = 0; i < cube.GetNumPieces(); i++) {
		if (cube.GetPieces()[i].GetType() == Piece::centre) {
			int current = CheckCross(cube.GetPieces()[i].GetColours()[0]);
			if (current > best) {
				cout << "Found better cross than previous. Previous: " << bestSide << "," << best;
				bestSide = cube.GetPieces()[i].GetColours()[0];
				best = current;
				cout << ". New: " << bestSide << "," << best << endl;
			}
		}
	}
	cout << "BestCross Complete. Best cross is: " << bestSide << " with score: " << best << endl;
	crossCentre = bestSide;
	return bestSide;
}

int Solver::BestMove() {
	cout << "Looking for best move..." << endl;
	crossCentre = BestCross();
	cout << "Done. Best move: " << endl;
	return 0;
}
