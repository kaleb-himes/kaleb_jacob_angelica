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
    node->data      = NULL;
    node->childern  = NULL;
    node->parent    = NULL;
    node->numChildern = 0;
    node->numParent   = 0;

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
  * Adds a parent to a node
  * @param in the address of node to add a parent to
  * @param parent the address of node to be added as a parent
  * @return 0 on success
  */
inline int Node_addParent(struct Node* in, struct Node* parent)
{
    if (in == NULL || parent == NULL) {
        printf("Error input argument to add parent was null\n");
        return 1;
    }

    /* case of first to be added */
    if (!in->numParent) {
        in->parent = malloc(sizeof(struct Node*));
        in->parent = parent;
    }
    else {
        /* reallocats memory for adding another parent pointer */
        in->parent = realloc(in->parent, (in->numParent + 1) *
                sizeof(struct Node*));
        if (in->parent == NULL) {
            printf("Fatal error adding a parent failed\n");
            return 1;
        }
        in->parent[in->numParent] = parent;    
    }

    in->numParent++;
    return 0;
}


/**
  * Adds a child to a node
  * @param in the address of node to add a child to
  * @param child the address of node to be added as a child
  * @return 0 on success
  */
inline int Node_addChild(struct Node* in, struct Node* child)
{
    if (in == NULL || child == NULL) {
        printf("Error input argument to add child was null\n");
        return 1;
    }

    /* case of first to be added */
    if (!in->numChildern) {
        in->childern = malloc(sizeof(struct Node*));
        in->childern = child;
    }
    else {
        /* reallocats memory for adding another child pointer */
        in->childern = realloc(in->childern, (in->numChildern + 1) *
                sizeof(struct Node*));
        if (in->childern == NULL) {
            printf("Fatal error adding a child failed\n");
            return 1;
        }
        in->childern[in->numChildern] = child;    
    }

    in->numChildern++;
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


