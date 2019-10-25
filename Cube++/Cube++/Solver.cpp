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
				} else if (distance > 1) {
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
					if (c.GetNum((Piece::COLOURS)notSolved[j]) >= 0)
						close++;
				}
				if (close == pieces[i].GetSize()) {
					int posContained = 0;
					for (int j = 0; j < pieces[i].GetSize(); j++) {
						for (int k = 0; k < pieces[i].GetSize(); k++) {
							if (pieces[i].GetColours()[j] == pieces[i].GetPositions()[k])
								posContained++;
						}
					}
					if (posContained != pieces[i].GetSize()) {
						if (pieces[i].GetType() == Piece::edge)
							counts.twoEdge.push_back(pieces[i]);
						else
							counts.twoCorner.push_back(pieces[i]);
					} else {
						if (pieces[i].GetType() == Piece::edge)
							counts.rotateEdge.push_back(pieces[i]);
						else
							counts.rotateCorner.push_back(pieces[i]);
					}
				} else {
					if (pieces[i].GetType() == Piece::edge)
						counts.positionEdge.push_back(pieces[i]);
					else
						counts.positionCorner.push_back(pieces[i]);
				}
			}
		}
	}
	cout << "Done.\nCentres: " << counts.centres.size() << endl;
	for (int i = 0; i < counts.centres.size(); i++)
		cout << counts.centres[i].GetColours()[0] << " ";
	cout << endl << "Edges: " << (counts.solvedEdge.size() + counts.oneEdge.size() + counts.twoEdge.size() + counts.rotateEdge.size() + counts.positionEdge.size())
		<< endl << "Solved: " << counts.solvedEdge.size() << endl;
	for (int i = 0; i < counts.solvedEdge.size(); i++) {
		for (int j = 0; j < counts.solvedEdge[i].GetSize(); j++)
			cout << counts.solvedEdge[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "Off by One: " << counts.oneEdge.size() << endl;
	for (int i = 0; i < counts.oneEdge.size(); i++) {
		for (int j = 0; j < counts.oneEdge[i].GetSize(); j++)
			cout << counts.oneEdge[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "Off by Two: " << counts.twoEdge.size() << endl;
	for (int i = 0; i < counts.twoEdge.size(); i++) {
		for (int j = 0; j < counts.twoEdge[i].GetSize(); j++)
			cout << counts.twoEdge[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "To Rotate: " << counts.rotateEdge.size() << endl;
	for (int i = 0; i < counts.rotateEdge.size(); i++) {
		for (int j = 0; j < counts.rotateEdge[i].GetSize(); j++)
			cout << counts.rotateEdge[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "To Position: " << counts.positionEdge.size() << endl;
	for (int i = 0; i < counts.positionEdge.size(); i++) {
		for (int j = 0; j < counts.positionEdge[i].GetSize(); j++)
			cout << counts.positionEdge[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "Corners: " << (counts.solvedCorner.size() + counts.positionCorner.size() + counts.oneCorner.size() + counts.twoCorner.size() +
		counts.rotateCorner.size()) << endl << "Solved: " << counts.solvedCorner.size() << endl;
	for (int i = 0; i < counts.solvedCorner.size(); i++) {
		for (int j = 0; j < counts.solvedCorner[i].GetSize(); j++)
			cout << counts.solvedCorner[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "Off by One: " << counts.oneCorner.size() << endl;
	for (int i = 0; i < counts.oneCorner.size(); i++) {
		for (int j = 0; j < counts.oneCorner[i].GetSize(); j++)
			cout << counts.oneCorner[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "Off by Two: " << counts.twoCorner.size() << endl;
	for (int i = 0; i < counts.twoCorner.size(); i++) {
		for (int j = 0; j < counts.twoCorner[i].GetSize(); j++)
			cout << counts.twoCorner[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "To Rotate: " << counts.rotateCorner.size() << endl;
	for (int i = 0; i < counts.rotateCorner.size(); i++) {
		for (int j = 0; j < counts.rotateCorner[i].GetSize(); j++)
			cout << counts.rotateCorner[i].GetColours()[j];
		cout << " ";
	}
	cout << endl << "To Position: " << counts.positionCorner.size() << endl;
	for (int i = 0; i < counts.positionCorner.size(); i++) {
		for (int j = 0; j < counts.positionCorner[i].GetSize(); j++)
			cout << counts.positionCorner[i].GetColours()[j];
		cout << " ";
	}
	cout << endl;
	return counts;
}

int Solver::ParseSide(char side, char from, char to, Piece::CONNECTED connect) {
	cout << "Rotating side: " << side << ". Rotating from: " << from << ". Rotating to: " << to
		<< "." << endl;
	cout << "Getting connected to find direction... ";
	int start = connect.GetNum((Piece::COLOURS)from);
	int end = connect.GetNum((Piece::COLOURS)to);
	int distance = end - start;
	cout << "Start: " << start<< ". End: "<< end << ". Direction: " << distance << endl;
	if (start == 0 && end == (size(connect.connected) - 1))
		distance = -1;
	else if (start == size(connect.connected) - 1 && end == 0)
		distance = 1;
	switch ((Piece::POSITIONS)side) {
	case Piece::front:
		if (distance > 0)
			return 0;
		else
			return 6;
	case Piece::back:
		if (distance > 0)
			return 1;
		else
			return 7;
	case Piece::top:
		if (distance > 0)
			return 2;
		else
			return 8;
	case Piece::bottom:
		if (distance > 0)
			return 3;
		else
			return 9;
	case Piece::left:
		if (distance > 0)
			return 4;
		else
			return 10;
	case Piece::right:
		if (distance > 0)
			return 5;
		else
			return 11;
	}
}

bool Solver::HasSolvedPieces(char side, COUNTS counts, Piece::TYPE type) {
	vector<Piece> inSide;
	for (int i = 0; i < cube.GetNumPieces(); i++)
		if (cube.GetPieces()[i].GetType() == type)
			inSide.push_back(cube.GetPieces()[i]);
	switch (type) {
	case Piece::edge:
		for (int i = 0; i < counts.solvedEdge.size(); i++)
			for (int j = 0; j < inSide.size(); j++)
				if (inSide[j] == counts.solvedEdge[i])
					return true;
		break;
	case Piece::corner:
		for (int i = 0; i < counts.solvedCorner.size(); i++)
			for (int j = 0; j < inSide.size(); j++)
				if (inSide[j] == counts.solvedCorner[i])
					return true;
		break;
	}
	return false;
}

Solver::Solver(Cube cube) {
	this->cube = cube;
}

void Solver::SetCube(Cube cube) {
	this->cube = cube;
}

int Solver::CheckCross(COUNTS counts, char side) {
	cout << "Checking if there is a cross in: " << side << "... ";
	int cross = 0;
	for (int i = 0; i < counts.solvedEdge.size(); i++)
		for (int j = 0; j < counts.solvedEdge[i].GetSize(); j++)
			if (counts.solvedEdge[i].GetColours()[j] == (Piece::COLOURS)side)
				cross += 5;
	for (int i = 0; i < counts.oneEdge.size(); i++)
		for (int j = 0; j < counts.oneEdge[i].GetSize(); j++)
			if (counts.oneEdge[i].GetColours()[j] == (Piece::COLOURS)side)
				cross += 3;
	for (int i = 0; i < counts.twoEdge.size(); i++)
		for (int j = 0; j < counts.twoEdge[i].GetSize(); j++)
			if (counts.twoEdge[i].GetColours()[j] == (Piece::COLOURS)side)
				cross += 2;
	for (int i = 0; i < counts.rotateEdge.size(); i++)
		for (int j = 0; j < counts.rotateEdge[i].GetSize(); j++)
			if (counts.rotateEdge[i].GetColours()[j] == (Piece::COLOURS)side)
				cross += 1;
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

char Solver::BestCross(COUNTS counts) {
	cout << "Finding best Cross..." << endl;
	int best = 0;
	char bestSide = 0;
	for (int i = 0; i < counts.centres.size(); i++) {
		int current = CheckCross(counts, counts.centres[i].GetColours()[0]);
		if (current > best) {
			cout << "Found better cross than previous. Previous: " << bestSide << "," << best;
			bestSide = cube.GetPieces()[i].GetColours()[0];
			best = current;
			cout << ". New: " << bestSide << "," << best << endl;
		}
	}
	cout << "BestCross Complete. Best cross is: " << bestSide << " with score: " << best << endl;
	return bestSide;
}

//int Solver::BestMove() {
//	cout << "Looking for best move..." << endl;
//	COUNTS c = GetCounts(cube.GetPieces(), cube.GetNumPieces());
//	if (c.solvedEdge.size() < 4) {
//		cout << "Cube barely solved." << endl;
//		char bestcross = BestCross();
//			if (c.oneEdge.size() == 1) {
//				cout << "Only one edge is off by one. Getting proper move to position... ";
//				Piece::CONNECTED connected;
//				char toMove;
//				char main;
//				char moveTo;
//				for (int i = 0; i < c.oneEdge[0].GetSize(); i++) {
//					if (c.oneEdge[0].GetColours()[i] == bestcross) {
//						connected = c.oneEdge[0].GetConnectedSide((Piece::POSITIONS)bestcross);
//						main = bestcross;
//					} else if (c.oneEdge[0].GetColours()[i] == c.oneEdge[0].GetPositions()[i]) {
//						connected = c.oneEdge[0].GetConnectedSide((Piece::POSITIONS)c.oneEdge[0].GetColours()[i]);
//						main = c.oneEdge[0].GetColours()[i];
//					} else {
//						toMove = c.oneEdge[0].GetColours()[i];
//						moveTo = c.oneEdge[0].GetPositions()[i];
//					}
//				}
//				bool clockwise = (connected.GetNum((Piece::COLOURS)toMove) + 1) % c.oneEdge[0].GetSize() == moveTo;
//				cout << "Done. Side to Move: " << toMove << ", C: " << clockwise << endl;
//				switch (main) {
//				case Piece::front:
//					if (clockwise)
//						return 0;
//					else
//						return 6;
//				case Piece::back:
//					if (clockwise)
//						return 1;
//					else
//						return 7;
//				case Piece::top:
//					if (clockwise)
//						return 2;
//					else
//						return 8;
//				case Piece::bottom:
//					if (clockwise)
//						return 3;
//					else
//						return 9;
//				case Piece::left:
//					if (clockwise)
//						return 4;
//					else
//						return 10;
//				case Piece::right:
//					if (clockwise)
//						return 5;
//					else
//						return 11;
//				}
//			} else if (c.oneEdge.size() > 1) {
//
//			} else {
//
//		}
//	} else if (c.solvedEdge.size() + c.solvedCorner.size() >= 7) {
//		for (int i = 0; i < cube.GetNumPieces(); i++) {
//			if (cube.GetPieces()[i].GetType() == Piece::centre) {
//				if (CheckLayer(0, cube.GetPieces()[i].GetColours()[0])) {
//					cout << "First layer solved" << endl;
//
//				} else {
//					cout << "First layer not solved. Determining if cube is mid algorithm" << endl;
//				}
//			}
//		}
//	}
//	cout << "Done. Best move: " << endl;
//	return 12;
//}

vector<int> Solver::BestMoves() {
	cout << "Looking for the best moves... ";
	vector<int> moves;
	COUNTS c = GetCounts(cube.GetPieces(), cube.GetNumPieces());
	char centre = BestCross(c);
	if (CheckCross(c, centre) != 20) {
		cout << "No complete cross. Complete cross... " << endl;
		vector<Piece> sidePieces;
		bool cont = false;
		if (c.oneEdge.size() > 0) {
			cout << c.oneEdge.size() << " edges One move away, checking for ones in best centre... ";
			int moved = 0;
			for (int i = 0; i < c.oneEdge.size(); i++) {
				for (int j = 0; j < c.oneEdge[i].GetSize(); j++) {
					int index = (j + 1) % c.oneEdge[i].GetSize();
					if (c.oneEdge[i].GetColours()[j] == centre && c.oneEdge[i].GetPositions()[j] != centre) {
						cout << "Found one, getting move: ";
						for (int k = 0; k < c.oneEdge[i].GetSize(); k++)
							cout << c.oneEdge[i].GetColours()[k];
						cout << endl;
						int move = ParseSide(c.oneEdge[i].GetPositions()[index], c.oneEdge[i].GetPositions()[j], c.oneEdge[i].GetColours()[j],
							c.oneEdge[i].GetConnectedSide(c.oneEdge[i].GetPositions()[index]));
						moves.push_back(move);
						cout << "Move returned: " << move << endl;
						moved++;
						break;
					} else if (c.oneEdge[i].GetColours()[j] == centre && c.oneEdge[i].GetPositions()[j] == centre) {
						cout << "Solved Position is the cross centre, checking for solved pieces in cross..." << endl;
						if (HasSolvedPieces(centre, c, Piece::edge)) {
							cout << "Solved pieces in centre, calculating moves to leave these solved" << endl;
							Piece::CONNECTED connect = c.oneEdge[i].GetConnectedSide(c.oneEdge[i].GetPositions()[index]);
							int move = ParseSide(c.oneEdge[i].GetPositions()[index], c.oneEdge[i].GetPositions()[j], c.oneEdge[i].GetColours()[j],
								c.oneEdge[i].GetConnectedSide(c.oneEdge[i].GetPositions()[index]));
							moves.push_back(move);
							moves.push_back(move);
							int moveIndex = connect.GetNum(c.oneEdge[i].GetPositions()[j]);
							moveIndex += 2;
							moveIndex = moveIndex % size(connect.connected);
							char movement = connect.connected[moveIndex];
							connect = c.oneEdge[i].GetConnectedSide((Piece::POSITIONS)movement);
							move = ParseSide(movement, , , connect);
						} else {
							cout << "No solved Pieces in centre, move this piece to solve" << endl;
							int move = ParseSide(c.oneEdge[i].GetColours()[j], c.oneEdge[i].GetColours()[index], c.oneEdge[i].GetPositions()[index],
								c.oneEdge[i].GetConnectedSide((Piece::POSITIONS)centre));
							moves.push_back(move);
						}
						moved++;
						break;
					} else {
						cout << "Not within Centre, looking for other pieces to move" << endl;
					}
				}
			}
			if (moved == 0)
				cont = true;
		}
		if (cont && c.twoEdge.size() > 0) {
			cout << "Checking pieces two moves away" << endl;
			for (int i = 0; i < c.twoEdge.size(); i++) {

			}
		}
	}
	cout << "Done." << endl;
	moves.push_back(12);
	return moves;
}
