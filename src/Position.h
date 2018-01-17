#pragma once

#include "oxygine-framework.h"
#include "Card.h"

using namespace oxygine;

DECLARE_SMART(Position, spPosition);
struct Position : public Actor
{
	bool flipped = false;
	spCard card;
};