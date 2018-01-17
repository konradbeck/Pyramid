#pragma once

#include "oxygine-framework.h"
#include "Card.h"

using namespace oxygine;

DECLARE_SMART(Location, spLocation);
struct Location : public Actor
{
	Vector2 position;
	spCard card;
};