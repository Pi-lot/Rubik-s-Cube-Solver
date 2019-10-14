#pragma once
#include "Cube.h"
#include <iostream>

class Solver {
private:
	char crossCentre;
	int centres[6];
	int const completeCross = 9;
	bool first;
	bool second;
	Cube cube;
public:
	Solver(Cube cube);
	void SetCube(Cube cube);
	int CheckCross(char side);
	bool CheckLayer(int no);
	char BestCross();
	int BestMove();
};

