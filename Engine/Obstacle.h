#pragma once

#include "Board.h"
#include "Snake.h"
#include <random>

class Obstacle
{
public:
	Obstacle();
	Obstacle(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;	
	bool IsInObstacle(const Location& target) const;
private:
	Location loc;
	static constexpr Color c = Colors::LightGray;
};
