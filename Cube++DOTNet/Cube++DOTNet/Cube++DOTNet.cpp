#include "pch.h"
#include <iostream>

using namespace System;
using namespace RubiksCube;

int main(array<System::String^>^ args) {
	Cube^ c = gcnew Cube;
	std::cout << c->GetCubeDisplay();
	return 0;
}
