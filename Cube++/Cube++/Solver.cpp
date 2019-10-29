#include "Solver.h"

Solver::COUNTS Solver::GetCounts(Piece *pieces, int SIZE) {
	cout << "Getting Piece Counts... ";
	COUNTS counts;
	cout << "Checking Pieces... ";
	for (int i = 0; i < SIZE; i++) {
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
				int start = c.GetNum((Piece::COLOURS)notSolvedPos[0]);
				int end = c.GetNum((Piece::COLOURS)notSolved[0]) + size(c.connected);
				int distance = (end - start) % size(c.connected);
				if ((distance == 1 || distance == 3) && !(end == - 1 || start == -1)) {
					if (pieces[i].GetType() == Piece::edge)
						counts.oneEdge.push_back(pieces[i]);
					else
						counts.oneCorner.push_back(pieces[i]);
				} else if (distance == 2 && !(end == -1 || start == -1)) {
					if (pieces[i].GetType() == Piece::edge)
						counts.twoEdge.push_back(pieces[i]);
					else
						counts.twoCorner.push_back(pieces[i]);
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
	if (start == -1 || end == -1) {
		cout << endl << "----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "--------------------------------- WRONG INPUT. CAN'T MOVE FROM/TO A SPECIFIED SIDE -----------------------------------" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	}
	int distance = end - start;
	cout << "Start: " << start << ". End: " << end << ". Direction: " << distance << endl;
	if (start == 0 && end == (size(connect.connected) - 1))
		distance = -1;
	else if (start == size(connect.connected) - 1 && end == 0)
		distance = 1;
	if (distance == -3)
		distance = 1;
	else if (distance == 3)
		distance = -1;
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
			for (int j = 0; j < cube.GetPieces()[i].GetSize(); j++)
				if (cube.GetPieces()[i].GetPositions()[j] == side)
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
	if (centre == NULL)
		centre = BestCross(c);
	if (oppCentre == NULL) {
		Piece::CONNECTED connect = cube.GetPieces()[0].GetConnectedSide((Piece::POSITIONS)centre);
		char side = connect.connected[0];
		connect = cube.GetPieces()[0].GetConnectedSide((Piece::POSITIONS)side);
		int baseIndex = connect.GetNum((Piece::COLOURS)centre);
		baseIndex += 2;
		baseIndex %= size(connect.connected);
		oppCentre = connect.connected[baseIndex];
	}
	cout << "Using Cross Centre: " << centre << endl;
	if (CheckCross(c, centre) != 20) {
		cout << "No complete cross. Complete cross... " << endl;
		if (c.oneEdge.size() > 0) {
			cout << c.oneEdge.size() << " edges One move away, checking for ones in best centre... ";
			for (int i = 0; i < c.oneEdge.size(); i++) {
				if (moves.size() == 0)
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
							break;
						} else if (c.oneEdge[i].GetColours()[j] == centre && c.oneEdge[i].GetPositions()[j] == centre) {
							cout << "Solved Position is the cross centre, checking for solved pieces in cross: ";
							for (int k = 0; k < c.oneEdge[i].GetSize(); k++)
								cout << c.oneEdge[i].GetColours()[k];
							cout << endl;
							if (HasSolvedPieces(centre, c, Piece::edge)) {
								cout << "Solved pieces in centre, calculating moves to leave these solved" << endl;
								Piece::CONNECTED connect = c.oneEdge[i].GetConnectedSide(c.oneEdge[i].GetPositions()[index]);
								int moveIndex = connect.GetNum((Piece::COLOURS)centre);
								moveIndex++;
								moveIndex %= size(connect.connected);
								int move = ParseSide(c.oneEdge[i].GetPositions()[index], c.oneEdge[i].GetPositions()[j], connect.connected[moveIndex],
									c.oneEdge[i].GetConnectedSide(c.oneEdge[i].GetPositions()[index]));
								moves.push_back(move);
								moves.push_back(move);
								moveIndex++;
								moveIndex %= size(connect.connected);
								char movement = connect.connected[moveIndex];
								connect = c.oneEdge[i].GetConnectedSide((Piece::POSITIONS)movement);
								move = ParseSide(movement, c.oneEdge[i].GetPositions()[index], c.oneEdge[i].GetColours()[index], connect);
								moves.push_back(move);
								connect = c.oneEdge[i].GetConnectedSide((Piece::POSITIONS)c.oneEdge[i].GetColours()[index]);
								moveIndex = connect.GetNum((Piece::COLOURS)movement);
								char next = connect.connected[(moveIndex + 1) % size(connect.connected)];
								move = ParseSide(c.oneEdge[i].GetColours()[index], movement, next, connect);
								moves.push_back(move);
								moves.push_back(move);
								cout << "Done" << endl;
							} else {
								cout << "No solved Pieces in centre, move this piece to solve" << endl;
								int move = ParseSide(c.oneEdge[i].GetColours()[j], c.oneEdge[i].GetPositions()[index], c.oneEdge[i].GetColours()[index],
									c.oneEdge[i].GetConnectedSide((Piece::POSITIONS)centre));
								moves.push_back(move);
							}
							break;
						}
					}
			}
			cout << "Moves: " << moves.size() << endl;
		}
		if (moves.size() == 0 && c.twoEdge.size() > 0) {
			cout << "Checking pieces two moves away. Size: " << c.twoEdge.size() << endl;
			for (int i = 0; i < c.twoEdge.size(); i++) {
				if (moves.size() == 0)
					for (int j = 0; j < c.twoEdge[i].GetSize(); j++) {
						int index = (j + 1) % c.twoEdge[i].GetSize();
						if (c.twoEdge[i].GetColours()[j] == centre && c.twoEdge[i].GetPositions()[j] != centre) {
							cout << "Found one that doesn't involve rotating the centre, ";
							for (int k = 0; k < c.twoEdge[i].GetSize(); k++)
								cout << c.twoEdge[i].GetColours()[k];
							cout << ", ";
							if (c.twoEdge[i].GetColours()[index] == c.twoEdge[i].GetPositions()[index]) {
								cout << "rotates same side twice. Getting moves..." << endl;
								Piece::CONNECTED connect = c.twoEdge[i].GetConnectedSide(c.twoEdge[i].GetPositions()[index]);
								int moveIndex = connect.GetNum(c.twoEdge[i].GetColours()[j]);
								moveIndex++;
								moveIndex %= size(connect.connected);
								int move = ParseSide(c.twoEdge[i].GetColours()[index], c.twoEdge[i].GetPositions()[j], connect.connected[moveIndex], connect);
								for (int k = 0; k < 2; k++)
									moves.push_back(move);
								cout << "Done" << endl;
							} else {
								cout << "rotates opposite centre then side it's in. Checking side if it's in contains a solved piece... ";
								if (HasSolvedPieces(c.twoEdge[i].GetPositions()[index], c, Piece::edge) || HasSolvedPieces(c.twoEdge[i].GetPositions()[j], c, Piece::edge)) {
									cout << "Has solved Pieces, getting moves to leave piece solved... ";
									if (c.twoEdge[i].GetPositions()[index] != centre) {
										Piece::CONNECTED connect = c.twoEdge[i].GetConnectedSide(c.twoEdge[i].GetPositions()[index]);
										int moveInit = ParseSide(c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetColours()[j], connect);
										moves.push_back((moveInit + 6) % 12);
										connect = c.twoEdge[i].GetConnectedSide((Piece::POSITIONS)oppCentre);
										int move = ParseSide(oppCentre, c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[index], connect);
										moves.push_back(move);
										moves.push_back(moveInit);
										move = ParseSide(c.twoEdge[i].GetColours()[index], oppCentre, c.twoEdge[i].GetPositions()[index],
											c.twoEdge[i].GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[index]));
										moves.push_back(move);
										moves.push_back(move);
									} else {
										int move = ParseSide(c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[index],
											c.twoEdge[i].GetConnectedSide(c.twoEdge[i].GetPositions()[j]));
										moves.push_back(move);
										move = ParseSide(c.twoEdge[i].GetColours()[index], c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetColours()[j],
											c.twoEdge[i].GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[index]));
										moves.push_back(move);
									}
									cout << "Done" << endl;
								} else {
									cout << "Side doesn't contain solved piece. Getting moves... ";
									for (int k = 0; k < c.twoEdge[i].GetSize(); k++)
										cout << c.twoEdge[i].GetColours()[k];
									cout << endl;
									Piece::CONNECTED connect = c.twoEdge[i].GetConnectedSide(c.twoEdge[i].GetPositions()[j]);
									int move = ParseSide(c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[index], connect);
									moves.push_back(move);
									connect = c.twoEdge[i].GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[index]);
									move = ParseSide(c.twoEdge[i].GetColours()[index], c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetColours()[j], connect);
									moves.push_back(move);
								}
								cout << "Done" << endl;
							}
							break;
						} else if (c.twoEdge[i].GetColours()[j] == centre && c.twoEdge[i].GetPositions()[j] == centre) {
							cout << "Piece within cross layer ";
							for (int k = 0; k < c.twoEdge[i].GetSize(); k++)
								cout << c.twoEdge[i].GetColours()[k];
							cout << ". Checking whether cross has solved pieces... ";
							if (HasSolvedPieces(c.twoEdge[i].GetColours()[j], c, Piece::edge)) {
								cout << "cross has solved pieces. Getting moves that leave these solved..." << endl;
								Piece::CONNECTED connect = c.twoEdge[i].GetConnectedSide(c.twoEdge[i].GetPositions()[index]);
								int moveIndex = connect.GetNum(c.twoEdge[i].GetPositions()[index]);
								moveIndex++;
								moveIndex %= size(connect.connected);
								int move = ParseSide(c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[j], connect.connected[moveIndex], connect);
								moves.push_back(move);
								moves.push_back(move);
								moveIndex++;
								moveIndex %= size(connect.connected);
								char movement = connect.connected[moveIndex];
								connect = c.twoEdge[i].GetConnectedSide((Piece::POSITIONS)movement);
								moveIndex = (connect.GetNum(c.twoEdge[i].GetPositions()[index]) + 1) % size(connect.connected);
								move = ParseSide(movement, c.twoEdge[i].GetPositions()[index], connect.connected[moveIndex], connect);
								moves.push_back(move);
								moves.push_back(move);
								connect = c.twoEdge[i].GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[index]);
								moveIndex = connect.GetNum((Piece::COLOURS)movement);
								char next = connect.connected[(moveIndex + 1) % size(connect.connected)];
								move = ParseSide(c.twoEdge[i].GetColours()[index], movement, next, connect);
								moves.push_back(move);
								moves.push_back(move);
								cout << "Done";
							} else {
								cout << "cross doesn't have solved pieces. Getting moves..." << endl;
								int move = ParseSide(c.twoEdge[i].GetColours()[j], c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[index],
									c.twoEdge[i].GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[j]));
								moves.push_back(move);
								moves.push_back(move);
								cout << "Done" << endl;
							}
							break;
						}
					}
			}
			cout << "Moves: " << moves.size() << endl;
		}
		if (moves.size() == 0 && c.rotateEdge.size() > 0) {
			cout << "Checking pieces to be rotated... ";
			for (int i = 0; i < c.rotateEdge.size(); i++) {
				if (moves.size() == 0) {
					for (int j = 0; j < c.rotateEdge[i].GetSize(); j++) {
						int index = (j + 1) % c.rotateEdge[i].GetSize();
						if (c.rotateEdge[i].GetColours()[j] == centre) {
							cout << "Piece related to centre. Getting moves to rotate piece... ";
							Piece::CONNECTED connect = c.rotateEdge[i].GetConnectedSide(c.rotateEdge[i].GetPositions()[j]);
							int moveIndex = connect.GetNum(c.rotateEdge[i].GetColours()[j]);
							moveIndex++;
							moveIndex %= size(connect.connected);
							int move = ParseSide(c.rotateEdge[i].GetPositions()[j], c.rotateEdge[i].GetColours()[j], connect.connected[moveIndex], connect);
							moves.push_back(move);
							char movement = connect.connected[moveIndex];
							connect = c.rotateEdge[i].GetConnectedSide(connect.connected[moveIndex]);
							moveIndex = connect.GetNum(c.rotateEdge[i].GetPositions()[j]);
							moveIndex += size(connect.connected);
							moveIndex--;
							moveIndex %= size(connect.connected);
							move = ParseSide(movement, c.rotateEdge[i].GetPositions()[j], connect.connected[moveIndex], connect);
							moves.push_back(move);
							char base = connect.connected[moveIndex];
							connect = c.rotateEdge[i].GetConnectedSide(connect.connected[moveIndex]);
							move = ParseSide(base, movement, c.rotateEdge[i].GetPositions()[j], connect);
							moves.push_back(move);
							connect = c.rotateEdge[i].GetConnectedSide((Piece::POSITIONS)movement);
							move = ParseSide(movement, base, c.rotateEdge[i].GetPositions()[j], connect);
							moves.push_back(move);
							connect = c.rotateEdge[i].GetConnectedSide(c.rotateEdge[i].GetPositions()[j]);
							move = ParseSide(c.rotateEdge[i].GetPositions()[j], base, movement, connect);
							moves.push_back(move);
							break;
						}
					}
				}
			}
			cout << "Moves: " << moves.size() << endl;
		}
		if (moves.size() == 0 && c.positionEdge.size() > 0) {
			cout << "Checking pieces to be postioned... ";
			for (int i = 0; i < c.positionEdge.size(); i++) {
				if (moves.size() == 0) {
					for (int j = 0; j < c.positionEdge[i].GetSize(); j++) {
						int index = (j + 1) % c.positionEdge[i].GetSize();
						if (c.positionEdge[i].GetColours()[j] == centre) {
							cout << "Piece related to centre. Getting moves to position piece... ";
							Piece::CONNECTED connect = c.positionEdge[i].GetConnectedSide(c.positionEdge[i].GetPositions()[j]);
							cout << endl << "-----------------------------------------------------------------------------------------------------------------------------";
							cout << "-----------------------------------------------------------------------------------------------------------------------------";
							cout << "-------------------------------------------------- NEEDS COMPLETION ---------------------------------------------------------";
							cout << "-----------------------------------------------------------------------------------------------------------------------------";
							cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
							break;
						} // Hasn't been triggered yet, so not worried just yet.
					}
				}
			}
			cout << "Moves: " << moves.size() << endl;
		}
	} else {
		cout << "Cross complete. Checking first layer.. ";
		if (!CheckLayer(0, centre)) {
			cout << "First layer not solved. Solve first layer... ";

		} else {
			cout << "First layer solved. Checking if second layer is solved... ";
			if (!CheckLayer(1, centre)) {
				cout << " Second layer not solved. Solve second layer... " << endl;

			} else {
				cout << "Second layer solved. Checking third layer cross state... ";
			}
		}
	}
	if (moves.size() == 0)
		moves.push_back(12);
	cout << "Done." << endl;
	return moves;
}

void Solver::ResetCentre() {
	centre = NULL;
}
