#include "Solver.h"

Solver::Solver(Cube cube) {
	for (int i = 0; i < size(centres); i++)
		centres[i] = (i + 4) * 9;
}

void Solver::SetCube(Cube cube) {
	this->cube = cube;
}

int Solver::CheckCross(char side) {
	cout << "Checking if there is a cross in: " << side  << "... ";
	bool cross = 0;
	int centre = 0;
	for (int i = 0; i < size(centres); i++)
		if (centres[i] == side) {
			centre = centres[i];
			break;
		}
	for (int i = centre - 3; i <= centre + 3; i += 2) {

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
	for (int i = 0; i < size(centres); i++) {
		char *cubeS = cube.CubeString();
		int current = CheckCross(cubeS[centres[i]]);
		if (current > best) {
			bestSide = crossCentre;
			best = current;
		}
		delete[] cubeS;
	}
	cout << "BestCross Complete. Best cross is: " << bestSide << endl;
	crossCentre = bestSide;
	return bestSide;
}

int Solver::BestMove() {
	cout << "Looking for best move..." << endl;
	BestCross();
	cout << "Done. Best move: " << endl;
	return 0;
}
