#pragma once

#include "Board.h"
#include "Keyboard.h"
#include <random>

class Snake
{
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow(std::mt19937& rng);
	void Update();
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool IsInTile(const Location& target) const;
	bool IsInTileExceptEnd(const Location& target) const;
	void Draw(Board& brd) const;
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(std::mt19937& rng);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		const Location& GetLocation() const;
		void Draw(Board& brd) const;
	private:
		Location loc;
		Color c;
		std::mt19937 rng;
		std::uniform_int_distribution<int> gDist;		
	};

	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;	
};

