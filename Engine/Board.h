#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder();
	int GetGridWidth() const;
	int GetGridHeight() const;
	int GetGridPadding() const;
	int GetGridBorder() const;
	bool IsInsideBoard(const Location& loc) const;
private:
	//Dimensión de una celda
	static constexpr int dimension = 20;
	//Ancho pantalla 800 px (800/20 = 40 celdas)
	static constexpr int width = 40;
	//Alto pantalla  600 px (600/20 = 30 celdas)
	static constexpr int height = 30;
	static constexpr int padding = 5;
	static constexpr int border = 1;
	static constexpr int borderDimension = border * dimension;
	static constexpr Color borderColor = Colors::Magenta;
	Graphics& gfx;
};
