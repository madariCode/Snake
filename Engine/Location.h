#pragma once

class Location
{
public:
	void Add(const Location& val);
	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	int x;
	int y;
};
