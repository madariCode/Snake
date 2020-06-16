#include "Fruit.h"
#include "Board.h"

Fruit::Fruit(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	Respawn(rng, brd, snake);
}

void Fruit::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(brd.GetGridBorder(), brd.GetGridWidth() - brd.GetGridBorder() - 1);
	std::uniform_int_distribution<int> yDist(brd.GetGridBorder(), brd.GetGridHeight() - brd.GetGridBorder() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc));

	loc = newLoc;
}

void Fruit::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Fruit::GetLocation() const
{
	return loc;
}
