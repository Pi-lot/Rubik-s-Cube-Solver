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

int main(array<System::String^>^ args) {
	Cube^ c = gcnew Cube;
	for (int i = 0; i < c->GetCubeDisplay()->Length; i++)
		Console::WriteLine(c->GetCubeDisplay()[i]);
	return 0;
}
