#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	Respawn(rng, brd, snake);
}

void Obstacle::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(brd.GetGridBorder(), brd.GetGridWidth() - brd.GetGridBorder() -1);
	std::uniform_int_distribution<int> yDist(brd.GetGridBorder(), brd.GetGridHeight() - brd.GetGridBorder() -1);

	Location newLoc;
	newLoc.x = xDist(rng);
	newLoc.y = yDist(rng);

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc));

	loc = newLoc;
}

void Obstacle::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Obstacle::GetLocation() const
{
	return loc;
}

bool Obstacle::IsInObstacle(const Location& target) const
{
	return loc == target;
}
