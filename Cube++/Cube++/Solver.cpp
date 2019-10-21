#include "Solver.h"

Solver::COUNTS Solver::GetCounts(Piece *pieces, int size) {
	cout << "Getting Piece Counts... ";
	COUNTS counts;
	cout << "Checking Pieces... ";
	for (int i = 0; i < size; i++) {
		if (pieces[i].GetType() == Piece::centre) {
			counts.centres.push_back(pieces[i]);
		} else {
			int solved = 0;
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
				Piece::CONNECTED c = pieces[i].GetConnectedSide((Piece::POSITIONS)side);
				unsigned int distance = c.GetNum((Piece::COLOURS)notSolved[0]) - c.GetNum((Piece::COLOURS)notSolvedPos[0]);
				if (distance == 1) {
					switch (pieces[i].GetType()) {
					case Piece::edge:

						break;
					}
					if (pieces[i].GetType() == Piece::edge)
						counts.oneEdge.push_back(pieces[i]);
					else {
						counts.oneCorner.push_back(pieces[i]);
					}
				}
				else if (distance > 1) {
					if (pieces[i].GetType() == Piece::edge)
						counts.twoEdge.push_back(pieces[i]);
					else {
						counts.twoCorner.push_back(pieces[i]);
					}
				}
			} else {
				int close = 0;
				for (int j = 0; j < notSolved.size(); j++) {
					Piece::CONNECTED c = pieces[i].GetConnectedSide((Piece::POSITIONS)notSolvedPos[j]);
				}
			}
		}
	}
	cout << "Done. Centres: " << counts.centres.size() << endl;
	for (int i = 0; i < counts.centres.size(); i++)
		cout << counts.centres[i].GetColours()[0] << endl;
	cout << "Edges: " << (counts.solvedEdge.size() + counts.oneEdge.size() + counts.twoEdge.size() + counts.positionEdge.size())
		<< endl << "Solved: " << counts.solvedEdge.size() << endl;
	for (int i = 0; i < counts.solvedEdge.size(); i++) {
		for (int j = 0; j < counts.solvedEdge[i].GetSize(); j++)
			cout << counts.solvedEdge[i].GetColours()[j];
		cout << endl;
	}
	cout << "Off by One: " << counts.oneEdge.size() << endl;
	for (int i = 0; i < counts.oneEdge.size(); i++) {
		for (int j = 0; j < counts.oneEdge[i].GetSize(); j++)
			cout << counts.oneEdge[i].GetColours()[j];
		cout << endl;
	}
	cout << "Off by Two: " << counts.twoEdge.size() << endl;
	for (int i = 0; i < counts.twoEdge.size(); i++) {
		for (int j = 0; j < counts.twoEdge[i].GetSize(); j++)
			cout << counts.twoEdge[i].GetColours()[j];
		cout << endl;
	}
	cout << "To Position: " << counts.positionEdge.size() << endl;
	for (int i = 0; i < counts.positionEdge.size(); i++) {
		for (int j = 0; j < counts.positionEdge[i].GetSize(); j++)
			cout << counts.positionEdge[i].GetColours()[j];
		cout << endl;
	}
	cout << "Corners: " << (counts.solvedCorner.size() + counts.positionCorner.size() + counts.oneCorner.size() + counts.twoCorner.size() + 
		counts.rotateCorner.size()) << endl << "Solved: " << counts.solvedCorner.size() << endl;
	for (int i = 0; i < counts.solvedCorner.size(); i++) {
		for (int j = 0; j < counts.solvedCorner[i].GetSize(); j++)
			cout << counts.solvedCorner[i].GetColours()[j];
		cout << endl;
	}
	cout << "Off by One: " << counts.oneCorner.size() << endl;
	for (int i = 0; i < counts.oneCorner.size(); i++) {
		for (int j = 0; j < counts.oneCorner[i].GetSize(); j++)
			cout << counts.oneCorner[i].GetColours()[j];
		cout << endl;
	}
	cout << "Off by Two: " << counts.twoCorner.size() << endl;
	for (int i = 0; i < counts.twoCorner.size(); i++) {
		for (int j = 0; j < counts.twoCorner[i].GetSize(); j++)
			cout << counts.twoCorner[i].GetColours()[j];
		cout << endl;
	}
	cout << "To Rotate: " << counts.rotateCorner.size() << endl;
	for (int i = 0; i < counts.rotateCorner.size(); i++) {
		for (int j = 0; j < counts.rotateCorner[i].GetSize(); j++)
			cout << counts.rotateCorner[i].GetColours()[j];
		cout << endl;
	}
	cout << "To Position: " << counts.positionCorner.size() << endl;
	for (int i = 0; i < counts.positionCorner.size(); i++) {
		for (int j = 0; j < counts.positionCorner[i].GetSize(); j++)
			cout << counts.positionCorner[i].GetColours()[j];
		cout << endl;
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
	COUNTS c = GetCounts(cube.GetPieces(), cube.GetNumPieces());
	if (c.solvedEdge.size() < 4) {
		cout << "Cube barely solved." << endl;
		char bestcross = BestCross();
			if (c.oneEdge.size() == 1) {
				cout << "Only one edge is off by one. Getting proper move to position... ";
				Piece::CONNECTED connected;
				char toMove;
				char main;
				char moveTo;
				for (int i = 0; i < c.oneEdge[0].GetSize(); i++) {
					if (c.oneEdge[0].GetColours()[i] == bestcross) {
						connected = c.oneEdge[0].GetConnectedSide((Piece::POSITIONS)bestcross);
						main = bestcross;
					} else if (c.oneEdge[0].GetColours()[i] == c.oneEdge[0].GetPositions()[i]) {
						connected = c.oneEdge[0].GetConnectedSide((Piece::POSITIONS)c.oneEdge[0].GetColours()[i]);
						main = c.oneEdge[0].GetColours()[i];
					} else {
						toMove = c.oneEdge[0].GetColours()[i];
						moveTo = c.oneEdge[0].GetPositions()[i];
					}
				}
				bool clockwise = (connected.GetNum((Piece::COLOURS)toMove) + 1) % c.oneEdge[0].GetSize() == moveTo;
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
			} else if (c.oneEdge.size() > 1) {

			} else {

		}
	} else if (c.solvedEdge.size() + c.solvedCorner.size() >= 7) {
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

vector<int> Solver::BestMoves() {
	cout << "Looking for the best moves... ";
	COUNTS c = GetCounts(cube.GetPieces(), cube.GetNumPieces());
	cout << "Done." << endl;
	vector<int> moves;
	moves.push_back(12);
	return moves;
}
