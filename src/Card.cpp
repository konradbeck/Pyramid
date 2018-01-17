#include "Card.h"
#include "Board.h"

/*

	Don't forget!
	It seems the removal and detaching is async.
	Therefore bools can be used as immeditate rules and the engine will take care of clearing memory


	Pausing the game still causes issues - Seems to only be when touched!

	Select one card - CRASH!

	It seems I cannot remove a tween before it has completed a cycle - NOT TRUE
	WHAT IS TRUE = -1 (infinity) loops cannot be removed
	-- Although ClipRect - seems to handle this
*/

Card::Card(Board* board) : board(board), selected(false), dead(false)
{
	type = rand() % 4 + 1;

	char name[255];
	safe_sprintf(name, "lego%d", type);

	setResAnim(res::ui.getResAnim(name));
	//setSize(cardSize);
	//setScale(scalar::randFloat(0.8f, 1.2f));
	setScale(Vector2(1.5f, 2.0f));
	
	//setAnchor(Vector2(0.5f, 0.5f));

	Vector2 center = getSize() / 2;
	//round center to avoid blurred image
	center.x = int(center.x);
	center.y = int(center.y);
	setAnchorInPixels(center);

	addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &Card::touched));

	attachTo(board);
}

void Card::touched(Event* event)
{
	TouchEvent* te = safeCast<TouchEvent*>(event);
	Vector2 pos = te->localPosition;

	if (selected)
	{
		unselect();
	}
	else
	{
		spCard previouslySelected = nullptr;

		for (spPosition position : board->deck->positions)
		{
			if (position->card && position->card != this && position->card->selected)
			{
				previouslySelected = position->card;
			}
		}

		//for (std::vector<spLocation> locationRows : board->locations)
		for (int y = 0; y < board->locations.size(); y++)
		{
			//for (spLocation location : locationRows)
			for (int x = 0; x < board->locations[y].size(); x++)
			{
				if (board->locations[y][x]->card && board->locations[y][x]->card == this)
				{
					// NEEED TO CONTINUE HERE
					int belowRow = y;
					int nextColumn = x;
					belowRow++;
					nextColumn++;

					if (board->locations.size() > belowRow && (board->locations[belowRow][x]->card || board->locations[belowRow][nextColumn]->card))
						return;
				}
				else if (board->locations[y][x]->card && board->locations[y][x]->card != this && board->locations[y][x]->card->selected)
				{
					previouslySelected = board->locations[y][x]->card;
				}
			}
		}

		select();

		if (previouslySelected)
		{
			if (previouslySelected->type == type)
			{
				previouslySelected->explode();
				explode();
			}
			else
			{
				previouslySelected->unselect();
				unselect();
			}
		}
	}
}

void Card::select()
{
	// STOP THINKING ABOUT OUTLINE - ALICIA SAID Boxes were a nicer approach
	/*
	
		But it might look weird with blocks covering blocks?
	
	*/

	selected = true;
	//setColor(Color::Blue);
	// tween = addTween(TweenGlow(Color::YellowGreen), 5000, -1, true, 0, Tween::ease_inOutCubic);
	// tween = addTween(createTween(TweenOutline(Color::Black), 1000, 1000, true));//, Tween::ease_inOutCubic);
	tween = addTween(createTween(Actor::TweenScale(2, 2), 2000, 1, true));
	//tween->addEventListener(TweenEvent::DONE, CLOSURE(this, &Card::tweenDone));
}

void Card::unselect()
{
	selected = false;
	//setColor(Color::White);
	removeTweens(true);
}

void Card::explode()
{
	float angle = 360 * (rand() % 2 ? -1 : 1);
	spTween tween = addTween(Actor::TweenRotationDegrees(angle), 500);
	addTween(Actor::TweenAlpha(0), 500);
	tween->setDoneCallback(CLOSURE(this, &Card::exploded));
}

void Card::exploded(Event*)
{
	/*
	for (std::vector<spLocation> locationRows : board->locations)
	{
		//for (spLocation location : locationRows)
		for (int x = 0; x < locationRows.size(); x++)
		{
			if (locationRows[x]->card == this)
			{
				locationRows.erase(locationRows.begin() + x);
				break;
			}
		}
	}
	
	for (int i = 0; i < board->cards.size(); i++)
	{
		if (board->cards[i] == this)
		{
			board->cards.erase(board->cards.begin() + i);
			break;
		}
	}*/

	dead = true;
	detach();
}

void Card::tweenDone(Event* event)
{
	//setColor(Color::Red);
}