#include "Deck.h"
#include "Board.h"

Deck::Deck(Board* board) : board(board)
{
	for (int i = 0; i < deckSize; i++)
	{
		spPosition position = new Position;
		position->card = new Card(board);
		//position->card->setVisible(false);
		//position->card->setPosition(Vector2(board->getSize().x / 2, board->getSize().y));
		positions.push_back(position);
	}

	attachTo(getStage());
}

void Deck::doUpdate(const UpdateState& state)
{
	for (spPosition position : positions)
	{
		if (position->card && !position->flipped)
		{
			position->card->setPosition(Vector2(board->getSize().x / 2.2f, board->getSize().y));
		}
	}
	
	for (int i = positions.size() - 1; i > 0; i--)
	{
		if (positions[i]->card && positions[i]->flipped)
		{
			positions[i]->card->setPosition(Vector2(board->getSize().x / 1.4f, board->getSize().y));
		}
	}
}

void Deck::deal()
{
	//for (spPosition position : positions)
	for (int i = positions.size() - 1; i > 0; i--)
	{
		if (positions[i]->card && !positions[i]->flipped)
		{
			positions[i]->flipped = true;
			break;
		}
	}
}