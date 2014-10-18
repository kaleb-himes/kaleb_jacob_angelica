/* Copyright 2014 Kaleb, Jacob, Angelica 
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
#include <stdlib.h>
#include <stdbool.h>
#include "JavaWinChecker.h"
#include "board_state.h"

#include <unistd.h>

struct heap_node {
    int  value;
    int  dir;   /* nodes can have 4 directions
                0 1 2
                3 X 3
                2 1 0 */
    struct heap_node* parent;
    struct heap_node* left;
    struct heap_node* right;
} heap_node;

struct hash_map {
    int id;
    int numNodes;
    struct heap_node** in;
} hash_map;

static int hash_map_sz;

struct heap_node* next; /* next node to add child to */
struct heap_node* top;  /* top of the heap */
struct hash_map*  map;  /* map of ids to node they belong in */

char current_player;

/**
  * Java entry point for winchecker
  * Function to check for a win
  * @param cPlayerTurn current player to check
  * @param cPlayerBoardLoc
  * @return a boolean value of win or not
  */
JNIEXPORT jboolean JNICALL Java_JavaWinChecker_check_1win
  (JNIEnv * env, jclass jc, jchar jch, jobjectArray jarr)
{
    /* Until we implement the logic just return false */
    bool bWin = false;

    /* check heap for a win */
    
    if (bWin)
	    return JNI_TRUE;
    else
        return JNI_FALSE;
	
}

//bool check_win (char cPlayerTurn, char cPlayerBoardLoc [][17])
//{
//    /* Until we implement the logic just return false */
//    bool bWin = false;
//
//    /* check heap for a win */
//    
//
//	return bWin;
//	
//}

/**
  * Create a hash for the x y cord
  */
int get_hash(int x, int y)
{
    return (x << 16) | y;
}

/**
  * Bubble up the nodes depending on there value in the heap
  */
int heap_bubble(struct heap_node* in)
{
    if (in == NULL)
        return 1;

    struct heap_node* temp;

    /* case of hitting top of heap*/
    if (in->parent == NULL) {
        top = in;
        return 0;
    }

    if (in->value > in->parent->value) {
       in->parent->right = in->right;
       temp = in->parent->left;
       in->parent->left = in->left;
       in->left = temp;
        if (in == in->parent->right) {
            in->right = in->parent;
        }
        else {
            in->left = in->parent;
        }
        in->parent = in->parent->parent;
        in->right->parent = in;
        in->left->parent = in;
        return heap_bubble(in);
    }

    return 0;
}

/**
  * Connect a new heap node to the bottom of the heap
  */
int heap_connect(struct heap_node* in)
{

    /* whos the parent? */
    if (next == NULL) {
        top = in;
        return 0;
    }

    if (next->left == NULL) {
        in->parent = next;
        next->left = in;
        return 0; 
    }

    if (next->right == NULL) {
        in->parent  = next;
        next->right = in;
        if (next->parent != NULL) {
            if (next == next->parent->right) {
                /* move all the way to farthes left leaf */
                next = top;
                while (next->left != NULL) { next = next->left; }
            }
            else {
                next = next->parent->right;
            }
        }
        return 0;
    }

    /* Case of no null leafs, move all the way to farthes left leaf */
    next = top;
    while (next->left != NULL) { next = next->left; }

    return 0;
}


/**
  * Creates a new heap node and bubbles it up through the heap.
  * @param dir the direction of the node
  * @param n the hash of the neighbor cord.
  * @param c the hash of the current cord.
  */
int node_create(int dir, int n, int c)
{
    struct heap_node* node;
    int i;

    node = malloc(sizeof(struct heap_node));
    if (node == NULL) {
        printf("Error creating a new node in winchecker\n");
        return -1;
    }

    /* add pointer too new node to the hash map */
    for (i = 0; i < hash_map_sz; i++) {
        if (n == map[i].id || c == map[i].id) {
            map[i].numNodes++;
            map[i].in = realloc(map[i].in, map[i].numNodes * sizeof(struct hash_node*));
            map[i].in[map[i].numNodes - 1] = node;
        }
    }

    /* create and bubble up the new node */
    node->value  = 2;
    node->right  = NULL;
    node->left   = NULL;
    node->parent = NULL;
    heap_connect(node);
    heap_bubble(node);

    return 0;
}


/**
  * Checks if the new placement can be merged with a current node
  * @param dir the direction to the neighbor
  * @parma n the hash value for the neighbor
  * @param c the hash value of the current
  */
int node_merge(int dir, int n, int c)
{
    int i, j;
    int inNode = 0;
    /* check if the neighbor belongs to a node */
    for (i = 0; i < hash_map_sz; i++) {
        /* if neighbor is in a node check direction */
        if (n == map[i].id) {
            for (j = 0; j < map[i].numNodes; j++) {
                if (map[i].in[j]->dir == dir) {
                    /* add new point to node and adjust heap */
                    map[i].in[j]->value++;
                    map[hash_map_sz - 1].in = realloc(map[hash_map_sz - 1].in, (map[hash_map_sz - 1].numNodes + 1) * sizeof(struct hash_node*));
                    map[hash_map_sz - 1].in[map[hash_map_sz - 1].numNodes] = map[i].in[j];
                    map[hash_map_sz - 1].numNodes++;
                    inNode = 1;
                    /* adjust heap due to value change */
                    heap_bubble(map[i].in[j]);
                }
            }
        }
    }
    /* not in node already so create one */
    if (!inNode) {
        node_create(dir, n, c);
    }

    return 0;
}


static inline int has_neighbor(int x, int y)
{
    char**  player_loc = NULL;
    int height;
    int width;
    int i;

    get_state(player_loc, &height, &width);

    /* if a neighbor is found the first attempt will be to merge with a node */
    for (i = (x <= 0)? 0 : (x -1); i < (x >= width)? width : (x + 1); x++) {
        /* below current */
        if (y > 0) {
            if (player_loc[i][y - 1] == current_player) {
                if (i == x)
                    node_merge(1, get_hash(i, y - 1), get_hash(x, y));
                if (i < x)
                    node_merge(2, get_hash(i - 1, y - 1), get_hash(x, y));
                if (i > x)
                    node_merge(3, get_hash(i + 1, y - 1), get_hash(x, y));
            }
        }

        /* above current */
        if (y < height) {
            if (player_loc[i][y + 1] == current_player) {
                if (i == x)
                    node_merge(1, get_hash(i, y + 1), get_hash(x, y));
                if (i < x)
                    node_merge(0, get_hash(i - 1, y + 1), get_hash(x, y));
                if (i > x)
                    node_merge(2, get_hash(i + 1, y + 1), get_hash(x, y));
            }
        }

        /* on same as current */
        if (player_loc[i][y] == current_player) {
            node_merge(3, get_hash(i, y), get_hash(x, y));
        }
    }

    return 0;
}

/**
  * Insert into the heap
  */
int heap_insert(int x, int y, char c)
{
    int i;
    int hashID;

    current_player = c;

    /* check if already added */
    if (hash_map_sz > 0) {
        hashID = get_hash(x, y);
        for (i = 0; i < hash_map_sz; i++) {
            if (map[i].id == hashID) {
                printf("X Y cord (%d , %d) has already been added\n", x, y);
                return 1;
            }
        }
    }

    if (map == NULL) {
        map  = malloc(sizeof(struct hash_map));
    }

    hash_map_sz++;
    map = realloc(map, hash_map_sz * sizeof(struct hash_map));
    map[hash_map_sz - 1].id = get_hash(x, y);
    map[hash_map_sz - 1].in = NULL;  


    /* if inserted x y cord has a neighbor create node to add to heap */
    has_neighbor(x, y);
    
    return 0;

}


/**
  * Remove node from heap
  */
int heap_remove()
{

    return 0;
}

