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
				Piece::CONNECTED c = Piece::GetConnectedSide((Piece::POSITIONS)side);
				int start = c.GetNum((Piece::COLOURS)notSolvedPos[0]);
				int end = c.GetNum((Piece::COLOURS)notSolved[0]) + size(c.connected);
				int distance = (end - start) % size(c.connected);
				if ((distance == 1 || distance == 3) && !(end == -1 || start == -1)) {
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
					Piece::CONNECTED c = Piece::GetConnectedSide((Piece::POSITIONS)notSolvedPos[j]);
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

vector<int> Solver::PositionCorner(char centrePos, char centreCol, char indexPos, char indexCol, char otherCol) {
	vector<int> moves;
	cout << "Getting moves to position piece... " << endl;
	Piece::CONNECTED connect = Piece::GetConnectedSide((Piece::POSITIONS)oppCentre);
	int start = connect.GetNum((Piece::COLOURS)indexPos);
	int end = connect.GetNum((Piece::COLOURS)otherCol) + size(connect.connected);
	int distance = (end - start) % size(connect.connected);
	int move;
	if (distance == 1 || distance == 3) {
		move = ParseSide(oppCentre, indexPos, otherCol, connect);
		moves.push_back(move);
	} else if (distance == 2) {
		move = move = ParseSide(oppCentre, indexPos, centrePos, connect);
		moves.push_back(move);
		moves.push_back(move);
	}
	connect = Piece::GetConnectedSide((Piece::POSITIONS)indexCol);
	move = ParseSide(indexCol, centreCol, otherCol, connect);
	moves.push_back(move);
	int last = ParseSide(oppCentre, otherCol, indexCol,
		Piece::GetConnectedSide((Piece::POSITIONS)oppCentre));
	moves.push_back(last);
	moves.push_back((move + 6) % 12);
	cout << "Position complete" << endl;
	return moves;
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

bool Solver::CheckLayer(int no, char layerCentre) {
	cout << "Checking layer: " << no << ", with centre: " << layerCentre << "... ";
	Piece *pieces = cube.GetPieces();
	int correct = 0;
	vector<Piece> layer;
	for (int i = 0; i < cube.GetNumPieces(); i++) {
		for (int j = 0; j < pieces[i].GetSize(); j++) {
			if (pieces[i].GetPositions()[j] == layerCentre)
				layer.push_back(pieces[i]);
		}
	}
	for (int i = 0; i < layer.size(); i++) {
		int right = 0;
		for (int j = 0; j < layer[i].GetSize(); j++)
			if (layer[i].GetPositions()[j] == layer[i].GetColours()[j])
				right++;
		if (right == layer[i].GetSize())
			correct++;
	}
	int completeNo;
	if (no == 0 || no == 2)
		completeNo = cube.SIZE * cube.SIZE;
	else
		completeNo = (cube.SIZE * cube.SIZE) - ((cube.SIZE - 2) * (cube.SIZE - 2));
	bool complete = completeNo == correct;
	if (no == 1) {
		Piece::CONNECTED c = Piece::GetConnectedSide((Piece::POSITIONS)layerCentre);
		char t = c.connected[0];
		c = Piece::GetConnectedSide((Piece::POSITIONS)t);
		int i = c.GetNum((Piece::POSITIONS)layerCentre);
		i += 2;
		i %= size(c.connected);
		complete = CheckMidLayer(layerCentre, c.connected[i]);
	}
	cout << "Done. True = " << true << ". Result: " << complete << ". Total = " << correct << ". ";
	return complete;
}

bool Solver::CheckMidLayer(char sideOne, char sideTwo) {
	cout << "Checking Mid layer, with centre: " << sideOne << "... ";
	Piece *pieces = cube.GetPieces();
	int correct = 0;
	vector<Piece> layer;
	Piece::CONNECTED test = Piece::GetConnectedSide((Piece::POSITIONS)'b');
	for (int i = 0; i < cube.GetNumPieces(); i++) {
		bool use = true;
		for (int j = 0; j < pieces[i].GetSize(); j++) {
			if (pieces[i].GetPositions()[j] == sideOne || pieces[i].GetPositions()[j] == sideTwo)
				use = false;
		}
		if (use)
			layer.push_back(pieces[i]);
	}
	for (int i = 0; i < layer.size(); i++) {
		int right = 0;
		for (int j = 0; j < layer[i].GetSize(); j++)
			if (layer[i].GetPositions()[j] == layer[i].GetColours()[j])
				right++;
		if (right == layer[i].GetSize())
			correct++;
	}
	int completeNo = (cube.SIZE * cube.SIZE) - ((cube.SIZE - 2) * (cube.SIZE - 2));
	bool complete = completeNo == correct;
	return complete;
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
		Piece::CONNECTED connect = Piece::GetConnectedSide((Piece::POSITIONS)centre);
		char side = connect.connected[0];
		connect = Piece::GetConnectedSide((Piece::POSITIONS)side);
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
								Piece::GetConnectedSide(c.oneEdge[i].GetPositions()[index]));
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
								Piece::CONNECTED connect = Piece::GetConnectedSide(c.oneEdge[i].GetPositions()[index]);
								int moveIndex = connect.GetNum((Piece::COLOURS)centre);
								moveIndex++;
								moveIndex %= size(connect.connected);
								int move = ParseSide(c.oneEdge[i].GetPositions()[index], c.oneEdge[i].GetPositions()[j], connect.connected[moveIndex],
									Piece::GetConnectedSide(c.oneEdge[i].GetPositions()[index]));
								moves.push_back(move);
								moves.push_back(move);
								moveIndex++;
								moveIndex %= size(connect.connected);
								char movement = connect.connected[moveIndex];
								connect = Piece::GetConnectedSide((Piece::POSITIONS)movement);
								move = ParseSide(movement, c.oneEdge[i].GetPositions()[index], c.oneEdge[i].GetColours()[index], connect);
								moves.push_back(move);
								connect = Piece::GetConnectedSide((Piece::POSITIONS)c.oneEdge[i].GetColours()[index]);
								moveIndex = connect.GetNum((Piece::COLOURS)movement);
								char next = connect.connected[(moveIndex + 1) % size(connect.connected)];
								move = ParseSide(c.oneEdge[i].GetColours()[index], movement, next, connect);
								moves.push_back(move);
								moves.push_back(move);
								cout << "Done" << endl;
							} else {
								cout << "No solved Pieces in centre, move this piece to solve" << endl;
								int move = ParseSide(c.oneEdge[i].GetColours()[j], c.oneEdge[i].GetPositions()[index], c.oneEdge[i].GetColours()[index],
									Piece::GetConnectedSide((Piece::POSITIONS)centre));
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
								Piece::CONNECTED connect = Piece::GetConnectedSide(c.twoEdge[i].GetPositions()[index]);
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
										Piece::CONNECTED connect = Piece::GetConnectedSide(c.twoEdge[i].GetPositions()[index]);
										int moveInit = ParseSide(c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetColours()[j], connect);
										moves.push_back((moveInit + 6) % 12);
										connect = Piece::GetConnectedSide((Piece::POSITIONS)oppCentre);
										int move = ParseSide(oppCentre, c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[index], connect);
										moves.push_back(move);
										moves.push_back(moveInit);
										move = ParseSide(c.twoEdge[i].GetColours()[index], oppCentre, c.twoEdge[i].GetPositions()[index],
											Piece::GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[index]));
										moves.push_back(move);
										moves.push_back(move);
									} else {
										int move = ParseSide(c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[index],
											Piece::GetConnectedSide(c.twoEdge[i].GetPositions()[j]));
										moves.push_back(move);
										move = ParseSide(c.twoEdge[i].GetColours()[index], c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetColours()[j],
											Piece::GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[index]));
										moves.push_back(move);
									}
									cout << "Done" << endl;
								} else {
									cout << "Side doesn't contain solved piece. Getting moves... ";
									for (int k = 0; k < c.twoEdge[i].GetSize(); k++)
										cout << c.twoEdge[i].GetColours()[k];
									cout << endl;
									Piece::CONNECTED connect = Piece::GetConnectedSide(c.twoEdge[i].GetPositions()[index]);
									int move = ParseSide(c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetPositions()[j], c.twoEdge[i].GetColours()[j], connect);
									moves.push_back(move);
									connect = Piece::GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[j]);
									move = ParseSide(c.twoEdge[i].GetColours()[j], c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[index], connect);
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
								Piece::CONNECTED connect = Piece::GetConnectedSide(c.twoEdge[i].GetPositions()[index]);
								int moveIndex = connect.GetNum(c.twoEdge[i].GetPositions()[index]);
								moveIndex++;
								moveIndex %= size(connect.connected);
								int move = ParseSide(c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[j], connect.connected[moveIndex], connect);
								moves.push_back(move);
								moves.push_back(move);
								moveIndex++;
								moveIndex %= size(connect.connected);
								char movement = connect.connected[moveIndex];
								connect = Piece::GetConnectedSide((Piece::POSITIONS)movement);
								moveIndex = (connect.GetNum(c.twoEdge[i].GetPositions()[index]) + 1) % size(connect.connected);
								move = ParseSide(movement, c.twoEdge[i].GetPositions()[index], connect.connected[moveIndex], connect);
								moves.push_back(move);
								moves.push_back(move);
								connect = Piece::GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[index]);
								moveIndex = connect.GetNum((Piece::COLOURS)movement);
								char next = connect.connected[(moveIndex + 1) % size(connect.connected)];
								move = ParseSide(c.twoEdge[i].GetColours()[index], movement, next, connect);
								moves.push_back(move);
								moves.push_back(move);
								cout << "Done";
							} else {
								cout << "cross doesn't have solved pieces. Getting moves..." << endl;
								int move = ParseSide(c.twoEdge[i].GetColours()[j], c.twoEdge[i].GetPositions()[index], c.twoEdge[i].GetColours()[index],
									Piece::GetConnectedSide((Piece::POSITIONS)c.twoEdge[i].GetColours()[j]));
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
							Piece::CONNECTED connect = Piece::GetConnectedSide(c.rotateEdge[i].GetPositions()[j]);
							int moveIndex = connect.GetNum(c.rotateEdge[i].GetColours()[j]);
							moveIndex++;
							moveIndex %= size(connect.connected);
							int move = ParseSide(c.rotateEdge[i].GetPositions()[j], c.rotateEdge[i].GetColours()[j], connect.connected[moveIndex], connect);
							moves.push_back(move);
							char movement = connect.connected[moveIndex];
							connect = Piece::GetConnectedSide(connect.connected[moveIndex]);
							moveIndex = connect.GetNum(c.rotateEdge[i].GetPositions()[j]);
							moveIndex += size(connect.connected);
							moveIndex--;
							moveIndex %= size(connect.connected);
							move = ParseSide(movement, c.rotateEdge[i].GetPositions()[j], connect.connected[moveIndex], connect);
							moves.push_back(move);
							char base = connect.connected[moveIndex];
							connect = Piece::GetConnectedSide(connect.connected[moveIndex]);
							move = ParseSide(base, movement, c.rotateEdge[i].GetPositions()[j], connect);
							moves.push_back(move);
							connect = Piece::GetConnectedSide((Piece::POSITIONS)movement);
							move = ParseSide(movement, base, c.rotateEdge[i].GetPositions()[j], connect);
							moves.push_back(move);
							connect = Piece::GetConnectedSide(c.rotateEdge[i].GetPositions()[j]);
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
						if (c.positionEdge[i].GetColours()[j] == centre && c.positionEdge[i].GetPositions()[j] == oppCentre) {
							cout << "Piece in base layer and needs positioning. Getting moves to position piece... ";
							Piece::CONNECTED connect = Piece::GetConnectedSide(c.positionEdge[i].GetPositions()[j]);
							int distance = size(connect.connected) + connect.GetNum(c.positionEdge[i].GetPositions()[index]) -
								connect.GetNum(c.positionEdge[i].GetPositions()[index]);
							distance %= size(connect.connected);
							int move;
							if (distance == 1) {
								move = ParseSide(oppCentre, c.positionEdge[i].GetPositions()[index], c.positionEdge[i].GetPositions()[index], connect);
								moves.push_back(move);
							} else if (distance == 2) {
								int next = connect.GetNum(c.positionEdge[i].GetPositions()[index]);
								next++;
								next %= size(connect.connected);
								move = ParseSide(oppCentre, c.positionEdge[i].GetPositions()[index], connect.connected[next], connect);
								moves.push_back(move);
								moves.push_back(move);
							}
							cout << "Done" << endl;
							break;
						} else if (c.positionEdge[i].GetColours()[j] == centre) {
							cout << endl << "----------------------------------------------------------------------------------------------------------------------" << endl;
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
							cout << "---------------------------------------------- NEEDS COMPLETION ------------------------------------------------------" << endl;
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
						}
					}
				}
			}
			cout << "Moves: " << moves.size() << endl;
		}
	} else {
		cout << "Cross complete. Checking first layer.. ";
		if (!CheckLayer(0, centre)) {
			cout << "First layer not solved. Solve first layer... ";
			vector<Piece> corners;
			for (int i = 0; i < c.oneCorner.size(); i++)
				for (int j = 0; j < c.oneCorner[i].GetSize(); j++)
					if (c.oneCorner[i].GetColours()[j] == centre)
						corners.push_back(c.oneCorner[i]);
			for (int i = 0; i < c.twoCorner.size(); i++)
				for (int j = 0; j < c.twoCorner[i].GetSize(); j++)
					if (c.twoCorner[i].GetColours()[j] == centre)
						corners.push_back(c.twoCorner[i]);
			for (int i = 0; i < c.rotateCorner.size(); i++)
				for (int j = 0; j < c.rotateCorner[i].GetSize(); j++)
					if (c.rotateCorner[i].GetColours()[j] == centre)
						corners.push_back(c.rotateCorner[i]);
			for (int i = 0; i < c.positionCorner.size(); i++)
				for (int j = 0; j < c.positionCorner[i].GetSize(); j++)
					if (c.positionCorner[i].GetColours()[j] == centre)
						corners.push_back(c.positionCorner[i]);
			for (int i = 0; i < corners.size(); i++) {
				if (moves.size() == 0) {
					for (int j = 0; j < corners[i].GetSize(); j++) {
						int indexOne = (j + 1) % corners[i].GetSize();
						int indexTwo = (j + 2) % corners[i].GetSize();
						cout << "Checking relevant corner pieces... ";
						if (corners[i].GetColours()[j] == centre && corners[i].GetPositions()[j] != oppCentre &&
							(corners[i].GetPositions()[indexOne] != centre && corners[i].GetPositions()[indexTwo] != centre &&
								corners[i].GetPositions()[j] != centre)) {
							cout << "Corner piece located in bottom layer with centre colour not in base layer. ";
							for (int k = 0; k < corners[i].GetSize(); k++)
								cout << corners[i].GetColours()[k];
							cout << ". Getting moves... ";
							int index;
							int other;
							if (corners[i].GetPositions()[indexOne] == oppCentre) {
								index = indexTwo;
								other = indexOne;
							} else {
								index = indexOne;
								other = indexTwo;
							}
							moves = PositionCorner(corners[i].GetPositions()[j], corners[i].GetColours()[j],
								corners[i].GetPositions()[index], corners[i].GetColours()[index], corners[i].GetColours()[other]);
							break;
						} else if (corners[i].GetColours()[j] == centre && corners[i].GetPositions()[j] != oppCentre &&
							(corners[i].GetPositions()[indexOne] == centre || corners[i].GetPositions()[indexTwo] == centre ||
								corners[i].GetPositions()[j] == centre)) {
							cout << "Piece located in first layer, must move out of layer first then position. Getting moves to get out of first layer... ";
							for (int k = 0; k < corners[i].GetSize(); k++)
								cout << corners[i].GetColours()[k];
							cout << "... ";
							if (corners[i].GetPositions()[j] == centre) {
								cout << "centre colour is in centre side... ";
								int move = ParseSide(corners[i].GetPositions()[indexOne], corners[i].GetColours()[j], corners[i].GetPositions()[indexTwo],
									Piece::GetConnectedSide(corners[i].GetPositions()[indexOne]));
								moves.push_back(move);
								int moveNext = ParseSide(oppCentre, corners[i].GetPositions()[indexOne], corners[i].GetPositions()[indexTwo],
									Piece::GetConnectedSide((Piece::POSITIONS)oppCentre));
								moves.push_back(moveNext);
								moves.push_back((move + 6) % 12);
								Piece::CONNECTED connect = Piece::GetConnectedSide((Piece::POSITIONS)oppCentre);
								int index = connect.GetNum(corners[i].GetPositions()[indexTwo]);
								if (connect.GetNum(corners[i].GetPositions()[indexOne]) > index || (index == 3 && connect.GetNum(corners[i].GetPositions()[indexOne]) == 0)) {
									index += size(connect.connected);
									index--;
								} else {
									index++;
								}
								index %= size(connect.connected);
								vector<int> nMoves = PositionCorner(connect.connected[index], corners[i].GetColours()[j], corners[i].GetPositions()[indexTwo],
									corners[i].GetColours()[indexOne], corners[i].GetColours()[indexTwo]);
								for (int k = 0; k < nMoves.size(); k++)
									moves.push_back(nMoves[k]);
							} else {
								cout << "centre colour isn't in centre side";
								int index;
								int other;
								if (corners[i].GetPositions()[indexOne] == centre) {
									index = indexTwo;
									other = indexOne;
								} else {
									index = indexOne;
									other = indexTwo;
								}
								int move = ParseSide(corners[i].GetPositions()[index], corners[i].GetColours()[j], corners[i].GetPositions()[j],
									Piece::GetConnectedSide(corners[i].GetPositions()[index]));
								moves.push_back(move);
								int nextMove = ParseSide(oppCentre, corners[i].GetPositions()[j], corners[i].GetPositions()[index],
									Piece::GetConnectedSide((Piece::POSITIONS)oppCentre));
								moves.push_back(nextMove);
								moves.push_back((move + 6) % 12);
								vector<int> nMoves = PositionCorner(corners[i].GetPositions()[j], corners[i].GetColours()[j], corners[i].GetPositions()[index],
									corners[i].GetColours()[other], corners[i].GetColours()[index]);
								for (int k = 0; k < nMoves.size(); k++)
									moves.push_back(nMoves[k]);
							}
							cout << "Done" << endl;
							break;
						} else  if (corners[i].GetColours()[j] == centre && corners[i].GetPositions()[j] == oppCentre &&
							(corners[i].GetPositions()[indexOne] != centre && corners[i].GetPositions()[indexTwo] != centre &&
								corners[i].GetPositions()[j] != centre)) {
							cout << "Corner piece is in base layer with centre colour in base side. Getting moves... ";
							for (int k = 0; k < corners[i].GetSize(); k++)
								cout << corners[i].GetColours()[k];
							cout << "... ";
							Piece::CONNECTED connect = Piece::GetConnectedSide((Piece::POSITIONS)oppCentre);
							int start = connect.GetNum((Piece::COLOURS)corners[i].GetPositions()[indexTwo]);
							int end = connect.GetNum((Piece::COLOURS)corners[i].GetColours()[indexOne]) + size(connect.connected);
							int distance = (end - start) % size(connect.connected);
							int move;
							if (distance == 1 || distance == 3) {
								move = ParseSide(oppCentre, corners[i].GetPositions()[indexTwo], corners[i].GetColours()[indexOne], connect);
								moves.push_back(move);
							} else if (distance == 2) {
								move = move = ParseSide(oppCentre, corners[i].GetPositions()[indexTwo], corners[i].GetPositions()[indexOne], connect);
								moves.push_back(move);
								moves.push_back(move);
							}
							int moveUndo = ParseSide(corners[i].GetColours()[indexOne], corners[i].GetColours()[j], corners[i].GetColours()[indexTwo],
								Piece::GetConnectedSide((Piece::POSITIONS)corners[i].GetColours()[indexOne]));
							moves.push_back(moveUndo);
							move = ParseSide(oppCentre, corners[i].GetColours()[indexTwo], corners[i].GetColours()[indexOne],
								Piece::GetConnectedSide((Piece::POSITIONS)oppCentre));
							moves.push_back(move);
							moves.push_back(move);
							moves.push_back((moveUndo + 6) % 12);
							vector<int> nMoves = PositionCorner(corners[i].GetColours()[indexTwo], corners[i].GetColours()[j],
								corners[i].GetColours()[indexOne], corners[i].GetColours()[indexOne], corners[i].GetColours()[indexTwo]);
							for (int k = 0; k < nMoves.size(); k++)
								moves.push_back(nMoves[k]);
							cout << "Done" << endl;
							break;
						}
					}
				}
			}
		} else {
			cout << "First layer solved. Checking if second layer is solved... ";
			if (!CheckLayer(1, centre)) {
				cout << "Second layer not solved. Solve second layer... Getting pieces to move... " << endl;
				vector<Piece> relevant;
				for (int i = 0; i < c.oneEdge.size(); i++) {
					bool base = false;
					for (int j = 0; j < c.oneEdge[i].GetSize(); j++) {
						if (c.oneEdge[i].GetColours()[j] == oppCentre)
							base = true;
					}
					if (!base)
						relevant.push_back(c.oneEdge[i]);
				}
				for (int i = 0; i < c.twoEdge.size(); i++) {
					bool base = false;
					for (int j = 0; j < c.twoEdge[i].GetSize(); j++) {
						if (c.twoEdge[i].GetColours()[j] == oppCentre)
							base = true;
					}
					if (!base)
						relevant.push_back(c.twoEdge[i]);
				}
				for (int i = 0; i < c.positionEdge.size(); i++) {
					bool base = false;
					for (int j = 0; j < c.positionEdge[i].GetSize(); j++) {
						if (c.positionEdge[i].GetColours()[j] == oppCentre)
							base = true;
					}
					if (!base)
						relevant.push_back(c.positionEdge[i]);
				}
				cout << "Done. Valid pieces: " << relevant.size() << ". ";
				if (moves.size() == 0 && relevant.size() > 0) {
					cout << "Finding piece position... ";
					for (int i = 0; i < relevant.size(); i++) {
						if (moves.size() == 0) {
							for (int j = 0; j < relevant[i].GetSize(); j++) {
								int index = (j + 1) % c.twoEdge[i].GetSize();
								if (relevant[i].GetPositions()[j] == oppCentre) {
									cout << "Piece located within base layer. Getting moves to solve... ";
									for (int k = 0; k < relevant[i].GetSize(); k++)
										cout << relevant[i].GetColours()[k];
									cout << "... ";
									Piece::CONNECTED connect = Piece::GetConnectedSide((Piece::POSITIONS)oppCentre);
									int indexPos = connect.GetNum(relevant[i].GetPositions()[index]);
									int thisPos = connect.GetNum(relevant[i].GetColours()[j]);
									int movePos = connect.GetNum(relevant[i].GetColours()[index]);
									int direction = movePos - thisPos;
									if (direction != 1 || direction != -1) {
										if (direction == 3)
											direction = -1;
										else if (direction == -3)
											direction = 1;
										else if (direction != 1 || direction != 1)
											cout << "Invalid direction!!! ";
									}
									movePos += size(connect.connected) + direction;
									movePos %= size(connect.connected);
									direction = movePos + size(connect.connected) - indexPos;
									direction %= size(connect.connected);
									int move;
									if (direction == 1) {
										move = ParseSide(oppCentre, connect.connected[indexPos], connect.connected[movePos], connect);
										moves.push_back(move);
									} else if (direction == 2) {
										move = ParseSide(oppCentre, relevant[i].GetColours()[index], connect.connected[movePos], connect);
										moves.push_back(move);
										moves.push_back(move);
									} else {
										move = ParseSide(oppCentre, connect.connected[indexPos], connect.connected[movePos], connect);
									}
									int secondMove = ParseSide(relevant[i].GetColours()[j], centre, relevant[i].GetColours()[index],
										Piece::GetConnectedSide((Piece::POSITIONS)relevant[i].GetColours()[j]));
									moves.push_back(secondMove);
									moves.push_back((move + 6) % 12);
									moves.push_back((secondMove + 6) % 12);
									move = ParseSide(oppCentre, relevant[i].GetColours()[index], relevant[i].GetColours()[j], connect);
									moves.push_back(move);
									secondMove = ParseSide(relevant[i].GetColours()[index], centre, relevant[i].GetColours()[j],
										Piece::GetConnectedSide((Piece::POSITIONS)relevant[i].GetColours()[index]));
									moves.push_back(secondMove);
									moves.push_back((move + 6) % 12);
									moves.push_back((secondMove + 6) % 12);
								}
							}
						}
					}
				}
				if (moves.size() == 0) {
					cout << "Only pieces are located within the second layer. Getting moves to move base layer... ";
					for (int i = 0; i < c.rotateEdge.size(); i++) {
						bool base = false;
						for (int j = 0; j < c.rotateEdge[i].GetSize(); j++) {
							if (c.rotateEdge[i].GetColours()[j] == oppCentre)
								base = true;
						}
						if (!base)
							relevant.push_back(c.rotateEdge[i]);
					}
					if (relevant.size() > 0) {
						int move = ParseSide(relevant[0].GetPositions()[0], centre, relevant[0].GetPositions()[1],
							Piece::GetConnectedSide(relevant[0].GetPositions()[0]));
						moves.push_back(move);
						int secondMove = ParseSide(oppCentre, relevant[0].GetPositions()[1], relevant[0].GetPositions()[0],
							Piece::GetConnectedSide((Piece::POSITIONS)oppCentre));
						moves.push_back(secondMove);
						moves.push_back((move + 6) % 12);
						moves.push_back(secondMove);
						move = ParseSide(relevant[0].GetPositions()[1], centre, relevant[0].GetPositions()[0],
							Piece::GetConnectedSide(relevant[0].GetPositions()[1]));
						moves.push_back(move);
						moves.push_back((secondMove + 6) % 12);
						moves.push_back((move + 6) % 12);
					}
				}
				cout << "Done." << endl;
			} else {
				cout << "Second layer solved. Checking third layer cross state...";
				vector<Piece> edges;
				for (int i = 0; i < c.oneEdge.size(); i++) {
					edges.push_back(c.oneEdge[i]);
				}
				for (int i = 0; i < c.twoEdge.size(); i++) {
					edges.push_back(c.twoEdge[i]);
				}
				for (int i = 0; i < c.positionEdge.size(); i++) {
					edges.push_back(c.positionEdge[i]);
				}
				for (int i = 0; i < c.rotateEdge.size(); i++) {
					edges.push_back(c.rotateEdge[i]);
				}
				vector<Piece> correct;
				if (edges.size() > 0) {
					for (int i = 0; i < edges.size(); i++) {
						for (int j = 0; j < edges[i].GetSize(); j++) {
							if (edges[i].GetColours()[j] == oppCentre && edges[i].GetPositions()[j] == oppCentre)
								correct.push_back(edges[i]);
						}
					}
					cout << "Cross State: " << correct.size() << ". ";
					if (correct.size() != 4) {
						cout << "Cross incomplete, ";
						Piece::CONNECTED base = Piece::GetConnectedSide((Piece::POSITIONS)oppCentre);
						char sideOne;
						char sideTwo;
						if (correct.size() == 0) {
							cout << "No Cross. Create L(ish) shape... ";
							sideOne = base.connected[1];
							sideTwo = base.connected[0];
						} else {
							cout << "Half cross: ";
							int one;
							int two;
							for (int i = 0; i < edges[0].GetSize(); i++) {
								if (correct[0].GetColours()[i] == oppCentre)
									one = base.GetNum(correct[0].GetPositions()[(i + 1) % correct[0].GetSize()]);
								if (correct[1].GetColours()[i] == oppCentre)
									two = base.GetNum(correct[1].GetPositions()[(i + 1) % correct[1].GetSize()]);
							}
							if (one - two == 2 || one - two == -2) {
								cout << "Line. ";
								sideOne = base.connected[(one + 1) % size(base.connected)];
								sideTwo = base.connected[one];
							} else {
								cout << "L(ish) shape. ";
								if (one == two + 1) {
									sideOne = base.connected[two];
									sideTwo = base.connected[one];
								} else {
									sideOne = base.connected[one];
									sideTwo = base.connected[two];
								}
							}
						}
						cout << "Getting moves... ";
						int moveOne = ParseSide(sideOne, oppCentre, sideTwo, Piece::GetConnectedSide((Piece::POSITIONS)sideOne));
						moves.push_back(moveOne);
						int moveTwo = ParseSide(sideTwo, sideOne, oppCentre, Piece::GetConnectedSide((Piece::POSITIONS)sideTwo));
						moves.push_back(moveTwo);
						int moveThree = ParseSide(oppCentre, sideTwo, sideOne, base);
						moves.push_back(moveThree);
						moves.push_back((moveTwo + 6) % 12);
						moves.push_back((moveThree + 6) % 12);
						moves.push_back((moveOne + 6) % 12);
						cout << "Done." << endl;
					} else {
						cout << "Cross Complete. Check Cross sides... ";
						Piece::CONNECTED connect = Piece::GetConnectedSide((Piece::POSITIONS)oppCentre);
						if (edges.size() == 2) {
							cout << "Two Edges are solved. ";
							int index;
							int sIndex;
							for (int i = 0; i < edges[0].GetSize(); i++) {
								if (edges[0].GetColours()[i] != oppCentre)
									index = i;
								if (edges[1].GetColours()[i] != oppCentre)
									sIndex = i;
							}
							int distance = size(connect.connected) + connect.GetNum(edges[0].GetPositions()[index]) -
								connect.GetNum(edges[1].GetPositions()[sIndex]);
							char sideOne;
							char sideTwo;
							if (distance == 2) {
								cout << "Pieces are opposite each other. ";
								sideTwo = edges[0].GetPositions()[index];
								int next = connect.GetNum(edges[0].GetPositions()[index]);
								next++;
								next %= size(connect.connected);
								sideOne = connect.connected[next];
							} else {
								cout << "Pieces are next to each other. ";
								if ((connect.GetNum(edges[0].GetPositions()[index]) + 1) % size(connect.connected) == connect.GetNum(edges[1].GetPositions()[sIndex])) {
									sideTwo = edges[0].GetPositions()[index];
									sideOne = edges[1].GetPositions()[sIndex];
								} else {
									sideTwo = edges[1].GetPositions()[sIndex];
									sideOne = edges[0].GetPositions()[index];
								}
							}
							cout << "Getting moves... ";
							int moveOne = ParseSide(sideTwo, sideOne, oppCentre, Piece::GetConnectedSide((Piece::POSITIONS)sideTwo));
							moves.push_back(moveOne);
							int moveTwo = ParseSide(oppCentre, sideOne, sideTwo, Piece::GetConnectedSide((Piece::POSITIONS)sideTwo));
							moves.push_back(moveTwo);
							moves.push_back(moveTwo);
							moves.push_back((moveOne + 6) % 12);
							moves.push_back(moveTwo);
							moves.push_back(moveOne);
							moves.push_back(moveTwo);
							moves.push_back((moveOne + 6) % 12);
							if (distance == 1)
								moves.push_back(moveTwo);
						} else if (edges.size() == 3) {
							cout << "One Edge solved. Getting moves... "; // --------------------------------------------------------------------------------------------
						} else {
							cout << "No Edges are solved. Getting moves... ";
							int move = ParseSide(oppCentre, connect.connected[0], connect.connected[1], connect);
							moves.push_back(move);
						}
						cout << "Done." << endl;
					}
				} else {
					cout << "Final Cross solved. Getting edge states...";
				}
			}
		}
	}
	if (moves.size() == 0)
		moves.push_back(12);
	cout << "Moves Found." << endl;
	return moves;
}

void Solver::ResetCentre() {
	centre = NULL;
}
