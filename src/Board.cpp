#include "Board.h"

Board::Board()
{
	//size.x = 7;
	size.y = 7;
	
	for (int y = 0; y < size.y; y++)
	{
		int rows = y;
		rows++;

		std::vector<spLocation> positionRows;

		for (int x = 0; x < rows; x++)
		{
			spLocation location = new Location;
			location->position = Vector2(x, y);
			location->card = new Card(this);
			positionRows.push_back(location);
		}

		locations.push_back(positionRows);
	}

	setResAnim(res::ui.getResAnim("bg"));
	setPosition(getStage()->getSize() / 2 - getSize() / 2);

	deck = new Deck(this);

	attachTo(getStage());

	button = new Sprite();
	//button->setScale(1, 1);	
	button->setResAnim(res::ui.getResAnim("button"));
	button->setPosition(Vector2(getSize().x / 2, getSize().y - (button->getWidth() / 2)));
	button->attachTo(this);
	button->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Board::buttonClicked));

	/*
	spButton btn = new Button;
	btn->setX(getWidth() - btn->getWidth() - 3);
	btn->setY(3);
	btn->attachTo(this);
	btn->addEventListener(TouchEvent::CLICK, CLOSURE(this, &Board::buttonClicked));*/
}

void Board::doUpdate(const UpdateState& state)
{
	// Move Blocks according to their location
	for (std::vector<spLocation> locationRows : locations)
	{
		float rowAlign = (getSize().x / 2) - ((locationRows.size() * cardSize.x) / 2);

		//for (spLocation location : locationRows)
		for (int x = 0; x < locationRows.size(); x++)
		{
			int rowCard = x;
			rowCard++;

			if (locationRows[x]->card)
			{
				if (locationRows[x]->card->dead)
				{
					locationRows[x]->card = nullptr;
					continue;
				}
				// StageSize / 2 - (RowSize * cardSize / 2)
				// 100 / 2 - (2 * 10 / 2) = 40
				// 40 + (10 + 10) + 40 = 100
				// 40 + (2 * 10)
				locationRows[x]->card->setPosition(Vector2(rowAlign + (rowCard * cardSize.x), locationRows[x]->position.y * cardSize.x));

				//                  (0, 0)                   // - 100 / 2 = 50	|	10 / 2 = 5  ---> 50 - 5  = 45 + 10 + 45 = 100
				//               (1, 0) (1, 1)               // - 100 / 2 = 50	|	20 / 2 = 10 ---> 50 - 10 = 40 + 20 + 40 = 100
				//           (2, 0) (2, 1) (2, 2)            // - 100 / 2 = 50	|	30 / 2 = 15 ---> 50 - 15 = 35 + 30 + 35 = 100
			}
		}
	}
}

void Board::buttonClicked(Event*)
{
	deck->deal();
}

void Board::free()
{
	this->detach();
}