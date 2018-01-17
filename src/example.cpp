#include "Board.h"
#include "res.h"

void example_preinit()
{

}

spBoard board;

void example_init()
{
	res::load();

	board = new Board();
}

void example_destroy()
{
    board->free();
	res::free();
}
void example_update()
{

}