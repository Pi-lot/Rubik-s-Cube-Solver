#include "Centre.h"

Centre::Centre(Centre::COLOURS Colour) {
	SIZE = 1;
	colours = new Centre::COLOURS[SIZE];
	colours[0] = Colour;
	positions = new Centre::POSITIONS[SIZE];
	switch (Colour) {
	case Piece::green:
		positions[0] = Piece::top;
		break;
	case Piece::blue:
		positions[0] = Piece::bottom;
		break;
	case Piece::yellow:
		positions[0] = Piece::front;
		break;
	case Piece::white:
		positions[0] = Piece::back;
		break;
	case Piece::red:
		positions[0] = Piece::right;
		break;
	case Piece::orange:
		positions[0] = Piece::left;
		break;
	default:
		break;
	}
}