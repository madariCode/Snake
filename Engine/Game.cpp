/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake({ 2,2 }),
	fruit(rng, brd, snake),
	obstacles()
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()

{
	if (isGameStarted && !isGameOver)
	{
		if (wnd.kbd.KeyIsPressed('W') || wnd.kbd.KeyIsPressed(VK_UP))
		{
			delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed('S') || wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed('A') || wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed('D') || wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1,0 };
		}

		++snakeMoveCounter;
		if (snakeMoveCounter >= snakeMovePeriod)
		{
			snakeMoveCounter = 0;
			const Location next = snake.GetNextHeadLocation(delta_loc);
			if (!brd.IsInsideBoard(next) ||
				snake.IsInTileExceptEnd(next))
			{
				isGameOver = true;
			}
			else
			{
				bool obstacleHit = false;
				int i = 0;
				while (i < nObstaclesMax - 1 && !obstacleHit)
				{
					obstacleHit = obstacles[i].IsInObstacle(next);
					++i;
				}
				if (obstacleHit)
				{
					isGameOver = true;
				}
				else
				{
					const bool eating = next == fruit.GetLocation();
					if (eating)
					{
						snake.Grow(rng);						
						obstacles[nObstacles - 1].Respawn(rng, brd, snake);

						++nObstacles;
					}
					snake.MoveBy(delta_loc);
					if (eating)
					{
						fruit.Respawn(rng, brd, snake);
					}
				}				
			}
			++snakeSpeedupCounter;
			if (snakeSpeedupCounter >= snakeSpeedupPeriod)
			{
				snakeSpeedupCounter = 0;
				snakeMovePeriod = std::max(snakeMovePeriod - 1, snakeMovePeriodMin);
			}
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			isGameStarted = true;
		}
	}
}

void Game::ComposeFrame()
{
	if (!isGameStarted)
	{
		SpriteCodex::DrawTitle((gfx.ScreenWidth / 2) - 10, (gfx.ScreenHeight / 2) - 10, gfx);
	}
	else
	{
		snake.Draw(brd);
		fruit.Draw(brd);
		brd.DrawBorder();

		for (int i = 0; i < nObstacles - 1; ++i)
		{
			obstacles[i].Draw(brd);
		}

		if (isGameOver)
		{
			SpriteCodex::DrawGameOver(290, 225, gfx);
		}
	}

}
