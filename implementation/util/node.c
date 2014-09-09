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

/**
  * Creates and allocates memory for a new node.
  * @return the pointer the the memory of the new node
  */
struct Node* Node_create()
{
    struct Node* node;

    /* initialize node */
    node = malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Error not enough memory to create new node!\n");
        return NULL;
    }
    pthread_mutex_init(&node->lock, NULL);
    /**
     * Will contain the heuristic value of the node
     * 1 = if curr_node is X, then has one neighbor that is also X
     * 2 = has two neighbors of same type contributing to a winning state
     * 3 = one move somewhere near this node will result in a win
     * 4 = WIN
     * @Heuristic value for win tracking
     */
    node->data          = NULL;

    /* The player who moved on node, X or O */
    node->player        = NULL;

    /*
     * Can have neighbors 
     * 0 = North, 
     * 1 = NorthEast, 
     * 2 = East, 
     * 3 = SouthEast, 
     * 4 = South, 
     * 5 = SouthWest, 
     * 6 = West, 
     * 7 = NorthWest
     */ 
    node->neighbor[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    node->numNeighbor  = 0;

    return node;
}

/**
  * Used to properly delete a node and free up its memory
  * @param the addres to the node to be deleted
  * @return 0 on success
  */
inline int Node_delete(struct Node* in)
{
    /* check if not null, then free */
    if (in->data)
        free(in->data);
    if (in->childern)
        free(in->childern);
    if (in->parent)
        free(in->parent);
    return 0;
}


/**
  * Adds a neighbor
  * @param in the address of node to add a parent to
  * @param parent the address of node to be added as a parent
  * @return 0 on success
  */
inline int Node_addNeighbor(struct Node* in, struct Node* neighbor)
{
    if (in == NULL || neighbor == NULL) {
        printf("Error input argument to add parent was null\n");
        return 1;
    }

    /* case of first to be added */
    if (!in->numNeighbor) {
        in->neighbor = malloc(sizeof(struct Node*));
        in->neighbor = neighbor;
    }
    else {
        /* reallocats memory for adding another neighbor pointer */
        in->neighbor = realloc(in->neighbor, (in->numNeighbor + 1) *
                sizeof(struct Node*));
        if (in->neighbor == NULL) {
            printf("Fatal error adding a parent failed\n");
            return 1;
        }
        in->neighbor[in->numNeighbor] = neighbor;    
    }

    in->numNeighbor++;
    return 0;
}

/**
  * Gets the data of the node. Use this function to make access to memory 
  * thread safe. Be sure to call function Node_doneData when done using the data
  * @parem in the address of the node to access memory from
  */
inline void* Node_getData(struct Node* in)
{
    if (in == NULL) {
        printf("Can not get data from null pointer\n");
        return NULL;
    }

    pthread_mutex_lock(in->lock);
    return in->data;
}


/**
  * Done using the nodes data. Use this function to make access to memory 
  * thread safe. 
  * @parem in the address of the node that user is done with
  */
inline void Node_doneData(struct Node* in)
{
    if (in == NULL) {
        printf("Called done data on a NULL node pointer\n");
        return;
    }

    pthread_mutex_unlock(in->lock);
}


