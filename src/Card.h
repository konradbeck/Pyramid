#pragma once

#include "oxygine-framework.h"
#include "res.h"
#include "TweenOutline.h"
#include "TweenGlow.h"

class Board;

using namespace oxygine;

const Vector2 cardSize(80, 130);//(getStage()->getSize() / 100);

DECLARE_SMART(Card, spCard);
struct Card : public Sprite
{
	bool selected;
	bool dead;
	int type;
	Board* board;
	spTween tween;

	Card(Board* board);

	void touched(Event* event);

	void select();
	void unselect();

	void explode();
	void exploded(Event*);

	void tweenDone(Event* event);
};