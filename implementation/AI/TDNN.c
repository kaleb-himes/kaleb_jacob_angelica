

#include "JavaTDNN.h"
#include <unistd.h>

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

int ideal_perdiction()
{

    return 0;
}


/**
  * Initialize the neural network
  * @return returns 0 on success and 1 on fail
  */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1init
  (JNIEnv * env, jclass jc)
{

    return 0;
}

/**
  * Make a move with the neural network
  * @param xyarray the x and y integer for placement
  * @return 0 for success 
  */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1make_1move
  (JNIEnv * env, jclass jc, jintArray jarr)
{

    return 0;
}


/**
  * Set option for potential prunning
  * @param prune a boolean flag to set prunning
  * @return 0 for success
  */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1prune
  (JNIEnv * env, jclass jc, jint ji)
{
    return 0;
}

/**
  * Free up memory allocated for neural network
  * @return 0 for success
  */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1free
  (JNIEnv * env, jclass jc)
{


    return 0;
}

/**
  * Set the depth of search if used
  * @param depth the depth to search
  * @return 0 for success
  */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1depth
  (JNIEnv * env, jclass jc, jint ji)
{

    return 0;
}
