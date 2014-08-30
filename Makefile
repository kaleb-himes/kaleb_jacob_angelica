# Copyright 2014 Kaleb, Jacob, Third_person
# 
# This file is part of Artificially Intelligent Polar Tic Tac Toe game.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with AI Polar Tic Tac Toe.  
#
# If not, see <http://www.gnu.org/licenses/>.

CC=gcc
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-2.0`

all: game

game: game.c initboard.c winlogic.c exit.c 
	$(CC) -Wall game.c initboard.c winlogic.c exit.c -o game $(GTKFLAGS)

.PHONY: clean all

clean:
	rm -f *.o game

