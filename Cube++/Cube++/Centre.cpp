#include "Centre.h"

Centre::Centre() {
	pieceType = centre;
	SIZE = 1;
	colours = new Piece::COLOURS {};
	*colours = green;
	positions = new Piece::POSITIONS {};
	*positions = top;
}

Centre::Centre(COLOURS colour) {
	pieceType = centre;
	SIZE = 1;
	colours = new Piece::COLOURS {};
	*colours = colour;
	positions = new Centre::POSITIONS;
	*positions = (POSITIONS)colour;
}
