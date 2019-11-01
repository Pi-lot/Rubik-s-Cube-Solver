#pragma once
#include "Cube.h"
#include <iostream>
#include <vector>

class Solver {
private:
	char centre = NULL;
	char oppCentre = NULL;
	Cube cube;
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
	vector<int> PositionCorner(char centrePos, char centreCol, char indexPos, char indexCol, char otherCol);
public:
	bool CheckLayer(int no, char layerCentre);
	Solver(Cube cube);
	void SetCube(Cube cube);
	vector<int> BestMoves();
	void ResetCentre();
};

