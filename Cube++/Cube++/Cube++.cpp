// Cube++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "Cube.h"
#include <vector>

using namespace std;

string CubePrint(Cube c) {
	cout << "Print Cube Start -------------------" << endl;
	char *cubeString = c.CubeString();
	string base = "";
	for (int i = 0; i < c.NOPOSITIONS; i++)
		base += cubeString[i];
	delete[] cubeString;
	cout << "Base:                " << base << endl;
	cout << "PrintPositions:      ";
	c.PrintPositions();
	cout << "PrintColours:        ";
	c.PrintColours();
	string sides[6] { "", "" ,"" ,"" ,"", "" };
	for (int i = 0; i < base.length(); i++) {
		sides[(int)(i / 9)] += base[i];
	}
	string seperator = "+-+-+-+";
	base = "";
	for (int i = 0; i < size(sides); i++) {
		string temp = seperator + '|';
		const char *s = sides[i].c_str();
		//cout << temp;
		for (int j = 0; j < sides[i].length(); j++) {
			//cout << sides[i][j];
			temp += s[j];
			temp += '|';
			if (j % c.SIZE == 2)
				temp += seperator + '|';
		}
		s = NULL;
		temp[temp.length() - 1] = ' ';
		base += temp;
		cout << temp << endl;
	}
	cout << "Print Cube End ---------------------" << endl;
	return base;
}

int main() {
	cout << "Hello World!" << endl;
	Cube cube;
	cout << true << endl;
	cout << "Start print" << endl;
	string printCube = CubePrint(cube);
	cout << printCube << endl;
	cout << "Print done ------------------------------------------------------------------------------" << endl;
	cout << cube.IsSolved() << endl;
	cube.RotateSide(Piece::top, true);
	cout << "One move print" << endl;
	printCube = CubePrint(cube);
	cout << printCube << endl;
	cout << "Print done ------------------------------------------------------------------------------" << endl;
	cube.RotateSide(Piece::top, false);
	cout << cube.IsSolved() << endl;
	cube.RotateSide(Piece::bottom, true);
	cube.RotateSide(Piece::right, true);
	cube.RotateSide(Piece::left, true);
	cout << cube.IsSolved() << endl << true << endl;
	cout << cube.IsSolved() << endl << true << endl;
	cube.RotateSide(Piece::left, false);
	cube.RotateSide(Piece::right, false);
	cube.RotateSide(Piece::bottom, false);
	cout << "Post 6 move print" << endl;
	printCube = CubePrint(cube);
	cout << printCube << endl;
	cout << "Print done ------------------------------------------------------------------------------" << endl;
	cube.RotateSide(Piece::bottom, true);
	cout << "Final print" << endl;
	printCube = CubePrint(cube);
	cout << printCube << endl;
	cout << "Print done ------------------------------------------------------------------------------" << endl;
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
