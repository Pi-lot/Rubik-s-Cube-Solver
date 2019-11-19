#pragma once
#include "Rubik's Cube++ Static/Cube.h"
#include "Rubik's Cube++ Static/Piece.h"
#include <iostream>
#include <vector>

using namespace cube;

class Solver {
private:
	char centre = NULL;
	char oppCentre = NULL;
	Cube cube;
	bool CheckLayer(int no, char layerCentre);
	struct COUNTS {
		vector<Piece> centres;
		vector<Piece> solvedEdge;
		vector<Piece> oneEdge;
		vector<Piece> twoEdge;
		vector<Piece> positionEdge;
		vector<Piece> rotateEdge;
		vector<Piece> solvedCorner;
		vector<Piece> oneCorner;
		vector<Piece> twoCorner;
		vector<Piece> positionCorner;
		vector<Piece> rotateCorner;
	};
	int CheckCross(COUNTS counts, char side);
	char BestCross(COUNTS counts);
	COUNTS GetCounts(Piece *pieces, int SIZE);
	int ParseSide(char side, char from, char to, Piece::CONNECTED connect);
	bool HasSolvedPieces(char side, COUNTS counts, Piece::TYPE type);
	vector<int> PositionCorner(Piece p, char centrePos, char centreCol, char indexPos, char indexCol, char otherCol);
public:
	Solver(Cube cube);
	void SetCube(Cube cube);
	vector<int> BestMoves();
	void ResetCentre();
};

