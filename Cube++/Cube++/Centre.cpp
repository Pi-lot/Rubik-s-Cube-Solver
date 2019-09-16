#include "Centre.h"

Centre::Centre() {
	pieceType = centre;
		SIZE = 1;
		colours = new Centre::COLOURS;
		*colours = green;
		positions = new Centre::POSITIONS;
		*positions = top;
}

Centre::Centre(COLOURS colour) {
	pieceType = centre;
		SIZE = 1;
		colours = new Centre::COLOURS;
		*colours = colour;
		positions = new Centre::POSITIONS;
		switch (colour) {
		case Piece::green:
			*positions = Piece::top;
			break;
		case Piece::blue:
			*positions = Piece::bottom;
			break;
		case Piece::yellow:
			*positions = Piece::front;
			break;
		case Piece::white:
			*positions = Piece::back;
			break;
		case Piece::red:
			*positions = Piece::right;
			break;
		case Piece::orange:
			*positions = Piece::left;
			break;
		}

		switch (colour) {
		case green:
			cout << "Green,";
			break;
		case blue:
			cout << "Blue,";
			break;
		case yellow:
			cout << "Yellow,";
			break;
		case white:
			cout << "White,";
			break;
		case red:
			cout << "Red,";
			break;
		case orange:
			cout << "Orange,";
			break;
		}
		cout << " - C";
		cout << endl;
}
