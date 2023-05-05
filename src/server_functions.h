#ifndef _SERVER_FUNCTIONS_H_
#define _SERVER_FUNCTIONS_H_
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "graph.h"
#include "dir.h"
#include <dlfcn.h>
#include <math.h>
#include "hole.h"
#include "moteur.h"

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>





// void print_queens(struct player p, int num_queens );


void get_opt(int argc, char* argv[], char* type, unsigned int *length, unsigned int* turns);

void sdl_display_queen(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS], int queens_number, int size);

void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],unsigned int queens_number);
void sdl_display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number, int size);

void table(unsigned int* queens[NUM_PLAYERS], int *t, unsigned int queens_number);

int *graph_table(struct graph_t *graph);

unsigned int* allouer_table(int length);

void queens_copy(unsigned int *queen[NUM_PLAYERS],unsigned int *q[NUM_PLAYERS] ,int m);


int start_player();

int next_player(int player);


#endif
