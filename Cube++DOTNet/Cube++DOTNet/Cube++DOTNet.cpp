#include "pch.h"
#include <iostream>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace System::Text;
using namespace System::Threading::Tasks;
using namespace System::Threading;
using namespace System::Diagnostics;
using namespace System::Collections;
using namespace RubiksCube;

void PrintCube(Cube^ cube) {
	cli::array<String^, 1>^ cubeString = cube->GetCubeDisplay();

	String^ breakLine = "        +-+-+-+";

	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[0][0] + "|" + cubeString[0][1] + "|" + cubeString[0][2] + "|");
	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[0][3] + "|" + cubeString[0][4] + "|" + cubeString[0][5] + "|");
	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[0][6] + "|" + cubeString[0][7] + "|" + cubeString[0][8] + "|");
	Console::WriteLine(breakLine);
	Console::WriteLine("+-+-+-+ +-+-+-+ +-+-+-+");
	Console::Write("|" + cubeString[2][0] + "|" + cubeString[2][1] + "|" + cubeString[2][2] + "| ");
	Console::Write("|" + cubeString[1][0] + "|" + cubeString[1][1] + "|" + cubeString[1][2] + "| ");
	Console::WriteLine("|" + cubeString[4][0] + "|" + cubeString[4][1] + "|" + cubeString[4][2] + "|");
	Console::WriteLine("+-+-+-+ +-+-+-+ +-+-+-+");
	Console::Write("|" + cubeString[2][3] + "|" + cubeString[2][4] + "|" + cubeString[2][5] + "| ");
	Console::Write("|" + cubeString[1][3] + "|" + cubeString[1][4] + "|" + cubeString[1][5] + "| ");
	Console::WriteLine("|" + cubeString[4][3] + "|" + cubeString[4][4] + "|" + cubeString[4][5] + "|");
	Console::WriteLine("+-+-+-+ +-+-+-+ +-+-+-+");
	Console::Write("|" + cubeString[2][6] + "|" + cubeString[2][7] + "|" + cubeString[2][8] + "| ");
	Console::Write("|" + cubeString[1][6] + "|" + cubeString[1][7] + "|" + cubeString[1][8] + "| ");
	Console::WriteLine("|" + cubeString[4][6] + "|" + cubeString[4][7] + "|" + cubeString[4][8] + "|");
	Console::WriteLine("+-+-+-+ +-+-+-+ +-+-+-+");
	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[3][0] + "|" + cubeString[3][1] + "|" + cubeString[3][2] + "|");
	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[3][3] + "|" + cubeString[3][4] + "|" + cubeString[3][5] + "|");
	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[3][6] + "|" + cubeString[3][7] + "|" + cubeString[3][8] + "|");
	Console::WriteLine(breakLine);
	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[5][0] + "|" + cubeString[5][1] + "|" + cubeString[5][2] + "|");
	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[5][3] + "|" + cubeString[5][4] + "|" + cubeString[5][5] + "|");
	Console::WriteLine(breakLine);
	Console::WriteLine("        |" + cubeString[5][6] + "|" + cubeString[5][7] + "|" + cubeString[5][8] + "|");
	Console::WriteLine(breakLine);
}

void MoveCubeSide(int num, Cube^ c) {
	if (num == 0)
		c->RotateSide(Cube::Positions::front, true);
	else if (num == 1)
		c->RotateSide(Cube::Positions::back, true);
	else if (num == 2)
		c->RotateSide(Cube::Positions::top, true);
	else if (num == 3)
		c->RotateSide(Cube::Positions::bottom, true);
	else if (num == 4)
		c->RotateSide(Cube::Positions::left, true);
	else if (num == 5)
		c->RotateSide(Cube::Positions::right, true);
	else if (num == 6)
		c->RotateSide(Cube::Positions::front, false);
	else if (num == 7)
		c->RotateSide(Cube::Positions::back, false);
	else if (num == 8)
		c->RotateSide(Cube::Positions::top, false);
	else if (num == 9)
		c->RotateSide(Cube::Positions::bottom, false);
	else if (num == 10)
		c->RotateSide(Cube::Positions::left, false);
	else if (num == 11)
		c->RotateSide(Cube::Positions::right, false);
}

int main(array<System::String^>^ args) {
	Cube^ cube = gcnew Cube();
	Random^ random = gcnew Random();
	Cube^ solvedCube = gcnew Cube();

	bool solved = false;
	PrintCube(cube);
	MoveCubeSide(1, cube);
	PrintCube(cube);
	return 0;
}
