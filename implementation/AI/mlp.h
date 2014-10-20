/*header file for mlp.c*/

#ifndef _mlp_h_
#define _mlp_h


void mlp_create(int in, int hid, int out, int lay);
void mlp_set_weights(float* w);
void mlp_forward_pass(float* input, float* output);
int  mlp_total_number_weights();
void mlp_close();


#endif
