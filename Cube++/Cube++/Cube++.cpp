// Cube++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>
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

void MoveCubeSide(Cube cube, int move) {
	switch (move) {
	case 0:
		cube.RotateSide(Piece::front, true);
		break;
	case 1:
		cube.RotateSide(Piece::back, true);
		break;
	case 2:
		cube.RotateSide(Piece::top, true);
		break;
	case 3:
		cube.RotateSide(Piece::bottom, true);
		break;
	case 4:
		cube.RotateSide(Piece::left, true);
		break;
	case 5:
		cube.RotateSide(Piece::right, true);
		break;
	case 6:
		cube.RotateSide(Piece::front, false);
		break;
	case 7:
		cube.RotateSide(Piece::back, false);
		break;
	case 8:
		cube.RotateSide(Piece::top, false);
		break;
	case 9:
		cube.RotateSide(Piece::bottom, false);
		break;
	case 10:
		cube.RotateSide(Piece::left, false);
		break;
	case 11:
		cube.RotateSide(Piece::right, false);
		break;
	}
}

int FindNextMove(Cube cube) {
	int centres[6];
	for (int i = 0; i < size(centres); i++) {
		centres[i] = (i * 9) + 4;
		cout << centres[i] << " ";
	}
	// Check for a cross

	cout << endl;
	return 0;
}

int main() {
	cout << "Welcome! (The front side is yellow and back is white)" << endl;
	Cube cube;
	random_device rd;
	do {
		for (int i = 0; i < 12; i++)
			MoveCubeSide(cube, (rd() % 12));
	} while (cube.IsSolved());
	cout << "Solve it!" << endl << CubePrint(cube);
	while (!cube.IsSolved()) {
		cout << "Which side would you like to move? ";
		string side;
		getline(cin, side);
		string temp;
		for (int i = 0; i < side.length(); i++)
			if (side[i] != '\n')
				temp += tolower(side[i]);
		side = temp;
		while (side != "front" && side != "back" && side != "top" &&
			side != "bottom" && side != "left" && side != "right" && side != "help") {
			cout << "Please input a correct side. ";
			getline(cin, side);
			temp = "";
			for (int i = 0; i < side.length(); i++)
				temp += tolower(side[i]);
			side = temp;
		}
		if (side != "help") {
			cout << "Rotate Clockwise? (based on sides perspective) y/n? ";
			char clockwise = tolower(getchar());
			while (clockwise != 'y' && clockwise != 'n') {
				cout << "Please input y or n. ";
				clockwise = tolower(getchar());
			}
			if (side == "front") {
				if (clockwise == 'y')
					MoveCubeSide(cube, 0);
				else
					MoveCubeSide(cube, 6);
			} else if (side == "back") {
				if (clockwise == 'y')
					MoveCubeSide(cube, 1);
				else
					MoveCubeSide(cube, 7);
			} else if (side == "top") {
				if (clockwise == 'y')
					MoveCubeSide(cube, 2);
				else
					MoveCubeSide(cube, 8);
			} else if (side == "bottom") {
				if (clockwise == 'y')
					MoveCubeSide(cube, 3);
				else
					MoveCubeSide(cube, 9);
			} else if (side == "left") {
				if (clockwise == 'y')
					MoveCubeSide(cube, 4);
				else
					MoveCubeSide(cube, 10);
			} else if (side == "right") {
				if (clockwise == 'y')
					MoveCubeSide(cube, 5);
				else
					MoveCubeSide(cube, 11);
			}
			cout << CubePrint(cube);
		} else {
			int move = FindNextMove(cube);
			switch (move) {
			case 0:
				cout << "The next move should be front clockwise";
				break;
			case 1:
				cout << "The next move should be back clockwise";
				break;
			case 2:
				cout << "The next move should be top clockwise";
				break;
			case 3:
				cout << "The next move should be bottom clockwise";
				break;
			case 4:
				cout << "The next move should be left clockwise";
				break;
			case 5:
				cout << "The next move should be right clockwise";
				break;
			case 6:
				cout << "The next move should be front anti-clockwise";
				break;
			case 7:
				cout << "The next move should be back anti-clockwise";
				break;
			case 8:
				cout << "The next move should be top anti-clockwise";
				break;
			case 9:
				cout << "The next move should be bottom anti-clockwise";
				break;
			case 10:
				cout << "The next move should be left anti-clockwise";
				break;
			case 11:
				cout << "The next move should be right anti-clockwise";
				break;
			}
			cout << endl;
		}
	}
	cout << "You solved the cube! Nice work! (Press enter to exit)";
	getchar();
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
