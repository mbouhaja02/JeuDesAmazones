#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include <stddef.h>
#include "dir.h"

/** The height (number of rows or columns) of the world */
#ifndef LENGHT
  #define LENGHT 8
#endif

/** The number of possible places in the world */
#define GRID_SIZE (LENGHT*LENGHT)
#define WHITE 1
#define BLACK 0
#define CASE -1

//this function create an empty graph 
struct graph_t * initialize_graph(int n){  
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            gsl_spmatrix_uint_set(mat, i, j, NO_DIR);
        }
    }
    struct graph_t * grid=malloc(sizeof(struct graph_t)); 
    grid->num_vertices = n*n;
    grid->t = mat;
    return grid;
}

void print_sparse_matrix(gsl_spmatrix_uint *mat) {
    printf("Sparse matrix:\n");
    printf("size1 = %zu, size2 = %zu\n", mat->size1, mat->size2);

// Loop over all gti pairs of vertices (n*n iterations)
for ( unsigned int i = 0; i < mat->size1; i++) {
    for ( unsigned int j = 0; j < mat->size2; j++) {
      printf("(%u) ",gsl_spmatrix_uint_get(mat, i, j)); 
    }
          if (((i%mat->size2) == 0)&&(i!=0)){
        printf("\n");
      }
      printf("\n");
  }
    }
//this function frees the momory blocks allocated for the graph
void free_graph(struct graph_t* g){
    free(g);
}

//this function fill an empty graph with relachionships
void initialize_graph_positions_classic(struct graph_t* g){ 
    size_t graph_size = g->t->size1;
    for (size_t i = 0; i < graph_size*graph_size ; i++) { //On parcourt toute la liste des graph_size**2 
        //si on est sur l'extremité gauche
        if( i % graph_size == 0){
           if( i == 0 ){ //la premiere case
                gsl_spmatrix_uint_set(g->t, i,i+1, DIR_EAST);
                gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
                gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_SE);
           }
           else if (i == graph_size*graph_size - graph_size){ //la case au coin gauche bas
                gsl_spmatrix_uint_set(g->t, i,i+1, DIR_EAST);
                gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_NORTH);
                gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_NE);
           }
           else { // les aures cases de la colonne
            gsl_spmatrix_uint_set(g->t, i, i+1, DIR_EAST);
            gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
            gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_SE);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);  
           }
        }
        //si on est sur l'estremité droite
        else if(i%graph_size == graph_size - 1){
            if (i == graph_size - 1){ // si on est sur le coin droit haut
                gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
                gsl_spmatrix_uint_set(g->t, i, i + graph_size, DIR_SOUTH);
                gsl_spmatrix_uint_set(g->t, i, i+ graph_size - 1, DIR_SW);
            }
            else if (i == graph_size*graph_size - 1 ){// si on est sur le coin droit bas
                gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
                gsl_spmatrix_uint_set(g->t, i, i - graph_size -1 , DIR_NW);
            }
            else{ //les autres cases de le colonne droite
                gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
                gsl_spmatrix_uint_set(g->t, i, i - graph_size -1 , DIR_NW);
                gsl_spmatrix_uint_set(g->t, i, i + graph_size , DIR_SOUTH);
            }
        }
        //si on est au milieu de la grille
        else{
            if ( 0 < i && i< graph_size ){ // la premiere ligne 
                gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
                gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
                gsl_spmatrix_uint_set(g->t, i, i + 1 , DIR_EAST);
                gsl_spmatrix_uint_set(g->t, i, i + graph_size - 1 , DIR_SW);
                gsl_spmatrix_uint_set(g->t, i, i + graph_size + 1 , DIR_SE);
            }
            else if( graph_size*graph_size - graph_size < i ){ //la derniere ligne
                gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
                gsl_spmatrix_uint_set(g->t, i, i + 1 , DIR_EAST);
                gsl_spmatrix_uint_set(g->t, i, i - graph_size - 1 , DIR_NW);
                gsl_spmatrix_uint_set(g->t, i, i - graph_size + 1 , DIR_NE);
            }
            else{ //les autres cases
                gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
                gsl_spmatrix_uint_set(g->t, i, i + 1 , DIR_EAST);
                gsl_spmatrix_uint_set(g->t, i, i - graph_size - 1 , DIR_NW);
                gsl_spmatrix_uint_set(g->t, i, i - graph_size + 1 , DIR_NE);
                gsl_spmatrix_uint_set(g->t, i, i + graph_size - 1 , DIR_SW);
                gsl_spmatrix_uint_set(g->t, i, i + graph_size + 1 , DIR_SE);
            }
        }
    }  
}

