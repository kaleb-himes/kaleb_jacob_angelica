/** Copyright 2014 
 * @author Kaleb, Jacob, Angelica 
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

/**
  * Initialize the neural network
  * @return returns 0 on success and 1 on fail
  */
int TDNN_init();                    /*  */

/**
  * Make a move with the neural network
  * @param xyarray the x and y integer for placement
  * @return 0 for success 
  */
int TDNN_make_move(int* xyarray);   /*  */

/**
  * Set option for potential prunning
  * @param prune a boolean flag to set prunning
  * @return 0 for success
  */
int TDNN_prune(int prune);          /*  */

/**
  * Free up memory allocated for neural network
  * @return 0 for success
  */
int TDNN_free();                    /*  */

/**
  * Set the depth of search if used
  * @param depth the depth to search
  * @return 0 for success
  */
int TDNN_depth(int depth);          /*  */

/* defined constant variables */
#define ALPHA .1 /* learning rate */

/* structures needed for implementation */
typedef struct {
    float delta; /* error */


} info;
