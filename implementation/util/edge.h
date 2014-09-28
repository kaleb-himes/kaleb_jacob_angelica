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

#include "node.h"

#ifndef EDGE_H
#define EDGE_H

struct Edge {
    pthread_mutex_t* lock;   /* to make access of edge thread safe */
    void*           weight; /* state of board determines weight assigned */
    struct Node**   head;   /* left or top node */
    struct Node**   tail;   /* bottom or right node */
};

/**
  * Creates and allocates memory for new edge
  * @return pointer to the memory of the new edge
  */  
struct Edge* Edge_create();

/**
  * Used to remove edge on board reset and free memory allocated
  * @param in the address to the edge deleted
  * @return 0 on success
  */  
inline int Edge_delete(struct Edge* in);

/**
  * Assigns a Head and Tail to edge
  * @param in the address of edge to add a head to
  * @param head the address of node that will become the head
  * @param tail the address of node that will become the tail
  * @return 0 on success
  */
inline int Edge_set(struct Edge* in, struct Node* head, struct Node* tail);

/**
  * Done using the edge data. Use this function to make access to memory thread
  * safe.
  * @param in the address of the edge that user is done modifying
  */  
inline void Edge_doneData(struct Edge* in);

#endif /* EDGE_H */

