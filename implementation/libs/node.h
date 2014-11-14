/** Copyright 2015 
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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#ifndef NODE_H
#define NODE_H

/**
  * @param data will contain the heuristic value based on board state
  * @param player X, O, or NULL
  * @param neighbor[8] 0:N, 1:NE, 2:E, 3:SE, 4:S, 5:SW, 6:W, 7:NW
  * @param numNeighbor if node==X, number of neighboring X's that contribute to a winning state.
  */  
struct Node {
    pthread_mutex_t* lock;     /* to make access of node thread safe           */
    void*           data;     /* user defined data, specialized for nodes use */
    void*           player;
    struct Node**   neighbor;
    int numNeighbor;
};

/**
  * Creates and allocates memory for a new node.
  * @return the pointer the the memory of the new node
  */
struct Node* Node_create(void);

/**
  * Used to properly delete a node and free up its memory
  * @param in the address to the node to be deleted
  * @return 0 on success
  */
inline int Node_delete(struct Node* in);

/**
  * Adds a neighbor to a node
  * @param in the address of node to add a neighbor to
  * @param newNeighbor the address of node to be added as a neighbor
  * @return 0 on success
  */
inline int Node_addNeighbor(struct Node* in, struct Node* newNeighbor);

/**
  * Gets the data of the node. Use this function to make access to memory 
  * thread safe. Be sure to call function Node_doneData when done using the data
  * @param in the address of the node to access memory from
  */
inline void* Node_getData(struct Node* in);

/**
  * Done using the nodes data. Use this function to make access to memory 
  * thread safe. 
  * @param in the address of the node that user is done with
  */
inline void Node_doneData(struct Node* in);

#endif /* NODE_H */

