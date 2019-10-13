// Cube++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "Cube.h"
#include <vector>

using namespace std;

string FormatSide(string side, bool addSpaces) {
	string spaces = "       ";
	string formatted = "";
	if (addSpaces)
		formatted = spaces;
	for (int i = 0; i < side.length(); i++) {
		if (i > 0 && ((side[i] == '|' && side[i - 1] == '+') || (side[i] == '+' && side[i - 1] == '|'))) {
			formatted += "\n";
			if (addSpaces)
				formatted += spaces;
		}
		formatted += side[i];
	}
	return formatted;
}

string CubePrint(Cube c) {
	char *cubeString = c.CubeString();
	string base = "";
	for (int i = 0; i < c.NOPOSITIONS; i++)
		base += cubeString[i];
	delete[] cubeString;
	string sides[6] { "", "" ,"" ,"" ,"", "" };
	for (int i = 0; i < base.length(); i++)
		sides[(int)(i / 9)] += base[i];
	string seperator = "+-+-+-+";
	base = "";
	for (int i = 0; i < size(sides); i++) {
		string temp = seperator + '|';
		const char *s = sides[i].c_str();
		for (int j = 0; j < sides[i].length(); j++) {
			temp += s[j];
			temp += '|';
			if (j % c.SIZE == 2)
				temp += seperator + '|';
		}
		s = NULL;
		temp[temp.length() - 1] = '\n';
		sides[i] = temp;
	}
	for (int i = 0; i < size(sides); i++)
		if (sides[i][(sides[i].length() / 2) - 1] == Piece::top)
			base += FormatSide(sides[i], true);
	// Middle Section -------------------------------------------------------------------------
	string middle[4] = {};
	for (int i = 0; i < size(sides); i++)
		if (sides[i][(sides[i].length() / 2) - 1] == Piece::left)
			middle[0] = FormatSide(sides[i], false);
	for (int i = 0; i < size(sides); i++)
		if (sides[i][(sides[i].length() / 2) - 1] == Piece::front)
			middle[1] = FormatSide(sides[i], false);
	for (int i = 0; i < size(sides); i++)
		if (sides[i][(sides[i].length() / 2) - 1] == Piece::right)
			middle[2] = FormatSide(sides[i], false);
	for (int i = 0; i < size(sides); i++)
		if (sides[i][(sides[i].length() / 2) - 1] == Piece::back)
			middle[3] = FormatSide(sides[i], false);
	int start = 0;
	int end = 0;
	for (int k = 0; k < 7; k++) {
		string row = "";
		int index = start;
		while (end == start) {
			index++;
			if (middle[0][index] == '\n')
				end = index;
		}
		for (int i = 0; i < size(middle); i++) {
			for (int j = start; j < end; j++) {
				if (middle[i][j] != '\n')
					row += middle[i][j];
			}
		}
		start = end;
		base += row + '\n';
	}
	// End Middle -----------------------------------------------------------------------------
	for (int i = 0; i < size(sides); i++)
		if (sides[i][(sides[i].length() / 2) - 1] == Piece::bottom)
			base += FormatSide(sides[i], true);
	return base;
}

int main() {
	cout << "Hello World!" << endl;
	Cube cube;
	cout << "True: " << true << endl;
	cout << "Start print" << endl;
	string printCube = CubePrint(cube);
	cout << printCube;
	cout << "Is Solved: " << cube.IsSolved() << endl;

	cube.RotateSide(Piece::bottom, true);
	cout << "One move print" << endl;
	printCube = CubePrint(cube);
	cout << printCube;
	cout << "Is Solved: " << cube.IsSolved() << endl;
	cout << "Undo one move" << endl;
	cube.RotateSide(Piece::bottom, false);
	cout << "Is Solved: " << cube.IsSolved() << endl;
	printCube = CubePrint(cube);
	cout << printCube;

	/*cube.RotateSide(Piece::bottom, true);
	cout << "One move print" << endl;
	printCube = CubePrint(cube);
	cout << printCube;
	cout << "Is Solved: " << cube.IsSolved() << endl;
	cout << "Undo one move" << endl;
	cube.RotateSide(Piece::bottom, false);
	cout << "Is Solved: " << cube.IsSolved() << endl;
	printCube = CubePrint(cube);
	cout << printCube;

	cube.RotateSide(Piece::right, true);
	cout << "One move print" << endl;
	printCube = CubePrint(cube);
	cout << printCube;
	cout << "Is Solved: " << cube.IsSolved() << endl;
	cout << "Undo one move" << endl;
	cube.RotateSide(Piece::right, false);
	cout << "Is Solved: " << cube.IsSolved() << endl;
	printCube = CubePrint(cube);
	cout << printCube;
	cube.RotateSide(Piece::bottom, true);*/
	//cube.RotateSide(Piece::bottom, true);
	//cube.RotateSide(Piece::right, true);
	//cube.RotateSide(Piece::left, true);
	//cout << cube.IsSolved() << endl << true << endl;
	//cout << cube.IsSolved() << endl << true << endl;
	//cube.RotateSide(Piece::left, false);
	//cube.RotateSide(Piece::right, false);
	//cube.RotateSide(Piece::bottom, false);
	//cout << "Post 6 move print" << endl;
	//printCube = CubePrint(cube);
	//cout << printCube << endl;
	//cout << "Print done ------------------------------------------------------------------------------" << endl;
	//cube.RotateSide(Piece::bottom, true);
	//cout << "Final print" << endl;
	//printCube = CubePrint(cube);
	//cout << printCube << endl;
	//cout << "Print done ------------------------------------------------------------------------------" << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
