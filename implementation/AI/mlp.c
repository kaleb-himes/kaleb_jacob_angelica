/** mpl.c
  * multi-layer perceptron neural network
  */

#include <stdio.h>
#include <stdlib.h>
#include "mlp.h"

struct node{
    float input;
    float* weight;
    float output;
    float error;
};

/* global struct arrays */
struct node* InputNode;
struct node* HiddenNode;
struct node* HiddenToOutput;
struct node* OutputNode;

/* global node structure */
int NumberInput;
int NumberHidden;
int NumberOutput;
int NumberHiddenLayers;


/**
  *Initializes the nodes for the network
  *@param in the number of input nodes
  *@param hid the number of hidden nodes
  *@param out the number of output nodes
  *@param lay the number of hidden layers
  */
void
mlp_create(int in, int hid, int out, int lay)
{
    NumberInput = in;
    NumberHidden = hid;
    NumberOutput = out;
    NumberHiddenLayers = lay;
    int i;
    InputNode = malloc((in + 1) * sizeof(struct node));
    if(lay > 0){
        for (i = 0; i < (in + 1); i++) {
            InputNode[i].weight = malloc(hid * sizeof(float));        
        }


        HiddenNode = malloc((hid + 1) * (lay-1) * sizeof(struct node));       
        if(HiddenNode == NULL && lay > 2) {
            printf("Error in setting up memory for hidden nodes\n");
        }
        for (i = 0; i < ((hid + 1) * (lay - 1)); i++) {
            HiddenNode[i].weight = malloc(hid * sizeof(float));
        }


        HiddenToOutput = malloc((hid + 1) * sizeof(struct node));
        for (i = 0; i < (hid + 1); i++) {
            HiddenToOutput[i].weight = malloc(out * sizeof(float));
        }
        if (HiddenToOutput == NULL) {
            printf("Error setting memory for hidden to output nodes.\n");
        }


    } else {
        /* case of no hidden layer */
        for (i = 0; i < (in + 1); i++) {
            InputNode[i].weight = malloc(out * sizeof(float));
        }
    }
    OutputNode = malloc((out) * sizeof(struct node));
    if(InputNode == NULL ||  OutputNode == NULL){
        printf("Error setting up memory for input or output nodes.\n");
    }
}

/**
  *Sets the float weight values for the network.
  *Starts with top left input node weights going out. Only input and hidden 
  *nodes since these are the nodes that have weights attached to output. Plus 
  *one each layer except output layer to account for bias.
  *@param wt the array of weight to set to.
  */
void
mlp_set_weights(float* wt)
{
    int i;
    int j;
    int z;
    int w = 0;
    /* make sure was created first */
    if (NumberInput < 1 || NumberOutput < 1){
        printf("Create function needs to be called first before"
               " setting weights.\n");
        exit(1);
    }
    if (NumberHiddenLayers > 0){
        for (i = 0; i < (NumberInput + 1); i++){
            for (j = 0; j < NumberHidden; j++){
                InputNode[i].weight[j] = wt[w];
            }
        }
        for (z = 0; z < (NumberHidden + 1) * (NumberHiddenLayers - 1); z++){
            for (j = 0; j < NumberHidden; j++){
                HiddenNode[z].weight[j] = wt[w];
            }
            i++;
        }
        for (z = 0; z < (NumberHidden + 1); z++){
            for (j = 0; j < NumberOutput; j++){
                HiddenToOutput[z].weight[0] = wt[w];
            } 
            i++;
        }
    }else {
    /* case of no hidden layers */
        for (i = 0; i < (NumberInput + 1); i++){
            for (j = 0; j < NumberOutput; j++){
                InputNode[i].weight[j] = wt[w];
            }
        }
    }
}

/**
  *Perform a forward pass through the network with current weights.
  *Assumes input has already been normalized.
  *@param *input an array of input values.
  *@param *output an array of output values set by functions side effect.
  */
void
mlp_forward_pass(float* input, float* output)
{
    int i, j, k, lays;
    float temp;
    /* input to input nodes */
    for (i = 0; i < NumberInput; i++) {
        InputNode[i].input = input[i];
    }
    if (NumberHiddenLayers > 0) {
        lays = 0; /* start from input and work toward output layer */
        /* input to first layer */
        if (NumberHiddenLayers > 1) {
            for (i = 0; i < NumberHidden; i++) {
                temp = 0.0;
                for (j = 0; j < (NumberInput + 1); j++) {
                    temp += InputNode[j].input * InputNode[j].weight[i];
                }
                HiddenNode[i].input = temp;
            }
            lays++;
        } else {
            for (i = 0; i < NumberHidden; i++) {
                temp = 0.0;
                for (j = 0; j < (NumberInput + 1); j++) {
                    temp += InputNode[j].input * InputNode[j].weight[i];
                }
                HiddenToOutput[i].input = temp;
            }
            lays++;
        }

        /* loop through middle layers*/
        while (lays < (NumberHiddenLayers - 1)) {
            i = (NumberHidden + 1) * (lays - 1);
            int start = i;
            int stop = i + NumberHidden;
            while (i < stop) {
                temp = 0.0;
                for (k = start; k < start + (NumberHidden + 1); k++) {
                    temp += HiddenNode[k].input * HiddenNode[k].weight[i];        
                }
                HiddenNode[i + NumberHidden + 1].input = temp;
                i++;
            }
            lays++;
        }
/******************************************************************************
 hidden layer to output 
******************************************************************************/        
        if (lays < NumberHiddenLayers) {
            int start = (NumberHidden + 1) * (NumberHiddenLayers - 2);
            int stop = (NumberHidden + 1) * (NumberHiddenLayers -1 );
            for (k = 0; k < NumberHidden; k++) {
                temp = 0.0;
                for (i = start; i < stop; i++) {
                    temp += HiddenNode[i].input * HiddenNode[i].weight[k];
                }
                HiddenToOutput[k].input = temp;
            }
        }
        
        for (i = 0; i < NumberOutput; i++) {
            temp = 0.0;
            for(k = 0; k < (NumberHidden + 1); k++) {


                temp += HiddenToOutput[k].input * HiddenToOutput[k].weight[i];
            }
            OutputNode[i].input = temp;
        }
/******************************************************************************
  Case of no hidden layer
******************************************************************************/
    } else {
        for (i = 0; i < NumberOutput; i++) {
            temp = 0.0;
            for (j = 0; j < (NumberInput + 1); j++) {
                temp += InputNode[j].input * InputNode[j].weight[i];
            }
            OutputNode[i].input = temp;
        }
    }

    /* place for adjustment if sigmoid on output is desired */
    for (i = 0; i < NumberOutput; i++) {
        output[i] = OutputNode[i].input;
    }
}

/**
  *Returns the total number of weights for the current network structure.
  */
int mlp_total_number_weights()
{
    if (NumberHiddenLayers > 0) {
        return ((NumberInput + 1) * NumberHidden) + 
            ((NumberHidden + 1) * (NumberHiddenLayers - 1) * NumberHidden) + 
            ((NumberHidden + 1 ) * NumberOutput);
    } else {
        return ((NumberInput + 1) * NumberOutput);
    }
}
/**
  *Frees up memory by derefrencing nodes.
  *Use when done with the network.
  */
void
mlp_close()
{
    free(InputNode);
    free(HiddenNode);
    free(HiddenToOutput);
    free(OutputNode);
}

