#include "Centre.h"

Centre::Centre(Centre::COLOURS Colour) {
	pieceType = centre;
	SIZE = 1;
	colours = new Centre::COLOURS;
	*colours = Colour;
	positions = new Centre::POSITIONS;
	switch (Colour) {
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
	default:
		break;
	}
}