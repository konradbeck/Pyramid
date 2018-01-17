#pragma once

#include "oxygine-framework.h"
#include "Position.h"

class Board;

using namespace oxygine;

DECLARE_SMART(Deck, spDeck);
struct Deck : public Sprite
{
	Board* board;

	const int deckSize = 24;

	spCard visibleCard;
	std::vector<spPosition> positions;

	Deck(Board* board);
	
	void doUpdate(const UpdateState& us);

	void deal();
};