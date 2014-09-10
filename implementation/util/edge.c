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

#include "edge.h"

/**
  * Creates and allocates memory for a new edge.
  * @return the pointer to the memory of the new edge
  */ 
struct Edge* Edge_create()
{
    struct Edge* edge;

    /* init edge */
    edge = malloc(sizeof(struct Edge));
    if (edge == NULL) {
        printf("Error not enough memory to create edge.\n");
        return NULL;
    }
    pthread_mutex_init(edge->lock, NULL);
    edge->weight    = 0;
    edge->head      = NULL;
    edge->tail      = NULL;

    return edge;
}

inline int Edge_delete(struct Edge* in)
{
    /* check if not null, then free */
    if (in->weight)
        free(in->weight);
    if (in->head)
        free(in->head);
    if (in->tail)
        free(in->tail);
    return 0;
}

inline int Edge_set(struct Edge* in, struct Node* head, struct Node* tail)
{
    if (in == NULL || head == NULL || tail == NULL) {
        printf("Error input argument to add edge was null.\n");
        return 1;
    }
    
    /* Jacob when you look at this, I saw you allocated memory for each neighbor
     * node in method Node_addNeighbor. Since I assume we will use:
     * Node_addNeighbor prior to Edge_set I'd like to discuss if we need to
     * alloc additional memory for the edge head and tail.*/
    in->head = &head;
    in->tail = &tail;
    
    return 0;
}

inline void Edge_doneData(struct Edge* in)
{
    if (in == NULL) {
        printf("Called done data on Null edge pointer.\n");
        return;
    }
    pthread_mutex_unlock(in->lock);
}

