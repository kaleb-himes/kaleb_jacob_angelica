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
#include "../JavaWinChecker.h"
#include "../gui_JavaPasser.h"

JNIEXPORT void JNICALL 
Java_gui_JavaPasser_pass(JNIEnv * j_env_pointer, 
                         jclass thisClass, 
                         jint x, 
                         jint y, 
                         jchar player) 
{
    printf("player: %c\n", player);
    printf("y coordinate: %d\n", y);
    printf("x coordinate: %d\n", x);

}
