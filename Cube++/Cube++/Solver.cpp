#include "Solver.h"

Solver::COUNTS Solver::GetCounts() {
	cout << "Getting Piece Counts... ";
	Piece *pieces = cube.GetPieces();
	COUNTS counts;
	cout << "Checking Pieces... ";
	for (int i = 0; i < cube.GetNumPieces(); i++) {
		if (pieces[i].GetType() == Piece::centre) {
			counts.centres.push_back(pieces[i]);
		} else {
			int solved;
			vector<char> notSolved;
			vector<char> notSolvedPos;
			for (int j = 0; j < pieces[i].GetSize(); j++) {
				if (pieces[i].GetColours()[j] == pieces[i].GetPositions()[j])
					solved++;
				else {
					notSolved.push_back(pieces[i].GetColours()[j]);
					notSolvedPos.push_back(pieces[i].GetPositions()[j]);
				}
			}
			if (solved == pieces[i].GetSize()) {
				if (pieces[i].GetType() == Piece::edge)
					counts.solvedEdge.push_back(pieces[i]);
				else
					counts.solvedCorner.push_back(pieces[i]);
			} else if (solved == 1) {
				char side;
				for (int j = 0; j < pieces[i].GetSize(); j++) {
					if (pieces[i].GetColours()[j] == pieces[i].GetPositions()[j]) {
						side = pieces[i].GetColours()[j];
						break;
					}
				}
				Piece::CONNECTED c = pieces[i].GetConnectedSide((Piece::COLOURS)side);
				unsigned int distance = c.GetNum((Piece::COLOURS)notSolved[0]) - c.GetNum((Piece::COLOURS)notSolvedPos[0]);
				if (distance == 1) {
					switch (pieces[i].GetType()) {
					case Piece::edge:

						break;
					}
					if (pieces[i].GetType() == Piece::edge)
						counts.oneEdge.push_back(pieces[i]);
					//else ()
				}
			} else {
				int close = 0;
				for (int j = 0; j < notSolved.size(); j++) {
					Piece::CONNECTED c = pieces[i].GetConnectedSide((Piece::POSITIONS)notSolvedPos[j]);
				}
			}
		}
	}
	return counts;
}

Solver::Solver(Cube cube) {
	this->cube = cube;
}

void Solver::SetCube(Cube cube) {
	this->cube = cube;
}

int Solver::CheckCross(char side) {
	cout << "Checking if there is a cross in: " << side << "... ";
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

bool Solver::CheckLayer(int no, char centre) {
	cout << "Checking layer: " << no << ", with centre: " << centre << "...";
	Piece *pieces = cube.GetPieces();
	int correct = 0;
	for (int i = 0; i < cube.GetNumPieces(); i++) {
		int right = 0;
		for (int j = 0; j < pieces[i].GetSize(); j++)
			if (pieces[i].GetPositions()[j] == centre && pieces[i].GetPositions()[j] == pieces[i].GetColours()[j])
				right++;
		if (right == pieces[i].GetSize())
			correct++;
	}
	int completeNo;
	if (no == 0 || no == 2)
		completeNo = cube.SIZE * cube.SIZE;
	else
		completeNo = (cube.SIZE * cube.SIZE) - ((cube.SIZE - 2) * (cube.SIZE - 2));
	bool complete = completeNo == correct;
	cout << " Done. True = " << true << ". Result: " << complete << ". Total = " << correct << endl;
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
	return bestSide;
}

int Solver::BestMove() {
	cout << "Looking for best move..." << endl;
	COUNTS c = GetCounts();
	if (c.solved.size() < 8) {
		cout << "Cube barely solved." << endl;
		char bestcross = BestCross();
		cout << "Finding closest edge... ";
		if (c.offByOne.size() > 0) {
			vector<Piece> edgesOffByOne;
			cout << "Getting edges off by one... ";
			for (int i = 0; i < c.offByOne.size(); i++) {
				if (c.offByOne[i].GetType() == Piece::edge) {
					edgesOffByOne.push_back(c.offByOne[i]);
				}
			}
			cout << "Done: " << edgesOffByOne.size() << ". ";
			if (edgesOffByOne.size() == 1) {
				cout << "Only one edge is off by one. Getting proper move to position... ";
				Piece::CONNECTED connected;
				char toMove;
				char main;
				char moveTo;
				for (int i = 0; i < edgesOffByOne[0].GetSize(); i++) {
					if (edgesOffByOne[0].GetColours()[i] == bestcross) {
						connected = edgesOffByOne[0].GetConnectedSide((Piece::POSITIONS)bestcross);
						main = bestcross;
					} else if (edgesOffByOne[0].GetColours()[i] == edgesOffByOne[0].GetPositions()[i]) {
						connected = edgesOffByOne[0].GetConnectedSide((Piece::POSITIONS)edgesOffByOne[0].GetColours()[i]);
						main = edgesOffByOne[0].GetColours()[i];
					} else {
						toMove = edgesOffByOne[0].GetColours()[i];
						moveTo = edgesOffByOne[0].GetPositions()[i];
					}
				}
				bool clockwise = (connected.GetNum((Piece::COLOURS)toMove) + 1) % edgesOffByOne[0].GetSize() == moveTo;
				cout << "Done. Side to Move: " << toMove << ", C: " << clockwise << endl;
				switch (main) {
				case Piece::front:
					if (clockwise)
						return 0;
					else
						return 6;
				case Piece::back:
					if (clockwise)
						return 1;
					else
						return 7;
				case Piece::top:
					if (clockwise)
						return 2;
					else
						return 8;
				case Piece::bottom:
					if (clockwise)
						return 3;
					else
						return 9;
				case Piece::left:
					if (clockwise)
						return 4;
					else
						return 10;
				case Piece::right:
					if (clockwise)
						return 5;
					else
						return 11;
				}
			} else if (edgesOffByOne.size() > 1) {

			} else {

			}
		}
	} else if (c.solved.size() >= 10) {
		for (int i = 0; i < cube.GetNumPieces(); i++) {
			if (cube.GetPieces()[i].GetType() == Piece::centre) {
				if (CheckLayer(0, cube.GetPieces()[i].GetColours()[0])) {
					cout << "First layer solved" << endl;

				} else {
					cout << "First layer not solved. Determining if cube is mid algorithm" << endl;
				}
			}
		}
	}
	cout << "Done. Best move: " << endl;
	return 12;
}
