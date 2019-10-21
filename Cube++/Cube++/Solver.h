#pragma once
#include "Cube.h"
#include <iostream>
#include <vector>

class Solver {
private:
	int const completeCross = 8;
	bool first = false;
	bool second = false;
	Cube cube;
	int CheckCross(char side);
	bool CheckLayer(int no, char centre);
	char BestCross();
	struct COUNTS {
		vector<Piece> centres;
		vector<Piece> solvedEdge;
		vector<Piece> oneEdge;
		vector<Piece> twoEdge;
		vector<Piece> positionEdge;
		vector<Piece> solvedCorner;
		vector<Piece> oneCorner;
		vector<Piece> twoCorner;
		vector<Piece> positionCorner;
		vector<Piece> rotateCorner;
	};
	COUNTS GetCounts();
public:
	Solver(Cube cube);
	void SetCube(Cube cube);
	int BestMove();
};

