#pragma once
#include "Cube.h"
#include <iostream>

class Solver {
private:
	char crossCentre;
	int const completeCross = 8;
	bool first = false;
	bool second = false;
	Cube cube;
public:
	Solver(Cube cube);
	void SetCube(Cube cube);
	int CheckCross(char side);
	bool CheckLayer(int no);
	char BestCross();
	int BestMove();
};

