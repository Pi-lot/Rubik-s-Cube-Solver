// Cube++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "Cube.h"

using namespace std;

int main() {
	int *test = new int[3];
	test[0] = 3;
	test[2] = 10;
	test[1] = 1;
	int *T = new int[3];
	copy(test, test + 3, T);
	T[0]++;
	T[1]++;
	T[2]++;
	for (int i = 0; i < 3; i++) {
		cout << test[i] << "|";
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		cout << T[i] << "|";
	}
	cout << endl;
	delete[] test, T;
	cout << "Hello World!" << endl;
	Cube cube;
	cout << true << endl;
	cout << cube.IsSolved() << endl;
	cube.RotateSide(Piece::front, true);
	cout << cube.IsSolved() << endl;
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
