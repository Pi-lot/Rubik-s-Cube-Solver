#pragma once
#include "Piece.h"
#include "Centre.h"
#include "Corner.h"
#include "Edge.h"

namespace RubiksCube {
	class Cube {
	public:
		enum Colours { green, yellow, red, white, orange, blue };
		enum PieceTypes { centre, edge, corner };
		enum Positions { top, bottom, front, back, left, right };
		enum MoveType { column, row };

		Cube();
		Cube(Cube cube);
		Cube(Positions* positions[]);
		~Cube();

		const int Size = 3;

		void SetPositions(Positions Side[]);
		bool SamePositions(Positions otherPositions[]);
		void RotateSide(Positions, bool);
		bool IsSolved();
	};
}
