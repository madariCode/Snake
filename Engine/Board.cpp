#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= border);
	assert(loc.x < width - border);
	assert(loc.y >= border);
	assert(loc.y < height - border);

	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension - padding, dimension - padding, c);
}

void Board::DrawBorder()
{
	gfx.DrawRectDim(0, 0, width * dimension, borderDimension, borderColor);
	gfx.DrawRectDim(0, (height * dimension) - borderDimension, width * dimension, borderDimension, borderColor);
	gfx.DrawRectDim(0, 0, borderDimension, height * dimension, borderColor);
	gfx.DrawRectDim((width * dimension) - borderDimension, 0, borderDimension, height * dimension, borderColor);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetGridPadding() const
{
	return padding;
}

int Board::GetGridBorder() const
{
	return border;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	return loc.x >= border && loc.x < width - border &&
		loc.y >= border && loc.y < height - border;
}
