

#include "TDNN.h"

/*
    Learning function is delta Wt = alpha ( z - V(st)) gradiant descent w V(st)

    Where Wt is a vector of the parameters of prediction function at time step t.
    Alpha is teh learning rate constant.
    Z is the target value.
    V(st) is the prediction for input at stat st
    gradiant w V(st) is a vector of partial derivatives of the prediction with 
        respect to the parameters w

    reference https://web.stanford.edu/group/pdplab/pdphandbook/handbookch10.html

   */

int depth; /* variable for depth of search */


/**
  * Initialize the neural network
  * @return returns 0 on success and 1 on fail
  */
int TDNN_init() 
{

    return 0;
}

/**
  * Make a move with the neural network
  * @param xyarray the x and y integer for placement
  * @return 0 for success 
  */
int TDNN_make_move(int* xyarray)
{

    return 0;
}


/**
  * Set option for potential prunning
  * @param prune a boolean flag to set prunning
  * @return 0 for success
  */
int TDNN_prune(int prune)
{
    /*  */
    return 0;
}

/**
  * Free up memory allocated for neural network
  * @return 0 for success
  */
int TDNN_free()
{
    /*  */


    return 0;
}

/**
  * Set the depth of search if used
  * @param depth the depth to search
  * @return 0 for success
  */
int TDNN_depth(int depth)
{
    /*  */


    return 0;
}
