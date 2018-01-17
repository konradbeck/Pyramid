#pragma once

#include "oxygine-framework.h"
#include "res.h"
#include "Location.h"
#include "Deck.h"

using namespace oxygine;

DECLARE_SMART(Board, spBoard);
struct Board : public Sprite
{
	Vector2 size;
	spSprite button;

	std::vector<std::vector<spLocation>> locations;
	//std::vector<spCard> cards;

	spDeck deck;

	Board();

	void buttonClicked(Event* event);

	void doUpdate(const UpdateState& us);
	void free();
};