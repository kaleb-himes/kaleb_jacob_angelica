/* Copyright 2014 Kaleb, Jacob, Third_person
 * 
 * This file is part of Artificially Intelligent Polar Tic Tac Toe game.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AI Polar Tic Tac Toe.  
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "initboard.h"

void clear_board (char cBoardLoc[][19], char *cTurn, bool *bWon)
{
	int y, x;
	
	for (y = 0; y < 20; y++)
	{
		for (x = 0; x < 20; x++)
			cBoardLoc [x][y] = 'E';
	}
	
	*cTurn = 'X';
	*bWon = false;
}
