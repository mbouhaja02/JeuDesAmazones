#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "dir.h"
#include "graph.h"
#include <time.h>


struct player_t player_black;


char const* get_player_name(){
    player_black.name = "seeer_seeeer";
    return player_black.name;
}

/*this function initializes inforamtions of the player and queens positions*/
void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
    player_black.id=player_id;
    player_black.graph=graph;
    player_black.num_queens=num_queens;
    player_black.turn=0;
    player_black.current_queens=queens[player_id];
    player_black.other_queens=queens[(player_id+1)%2];
}


/*this function selects a random move for the player*/
struct move_t random_move(struct move_t move, enum dir_t dir, unsigned int queen_index, struct player_t player){
    (void) player;
    move.queen_src=player_black.current_queens[queen_index];
    move.queen_dst=random_dst(player_black.graph,dir,player_black.current_queens[queen_index], player_black);
    player_black.current_queens[queen_index]=move.queen_dst;
    unsigned int queen=move.queen_dst;
    enum dir_t dir2=available_dir(queen,player_black.graph,dir,player_black);
    if(dir2==NO_DIR){
        move.arrow_dst=move.queen_src;
    }
    else {
        move.arrow_dst=random_dst(player_black.graph,dir2,move.queen_dst,player_black);
    }
    return move;
}

/*the play function it exectus the previous move and returns a new move for the player*/
struct move_t play(struct move_t previous_move){
    if(previous_move.queen_dst!= (unsigned int) -1 && previous_move.queen_dst!= (unsigned int) -1 )
        execute_move(previous_move,player_black.graph,player_black.other_queens);
    struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
    int r=rand()%player_black.num_queens;
    unsigned int queen_index=r;
    int queen=player_black.current_queens[r];
    enum dir_t dir=NO_DIR;
    unsigned int cmp=0;
    while(dir==NO_DIR && cmp<player_black.num_queens){
        cmp++;
        queen_index=r;
        queen=player_black.current_queens[queen_index];
        dir=available_dir(queen,player_black.graph,NO_DIR,player_black);
        r=(r+1)%player_black.num_queens;
       
    }
    if(dir==NO_DIR){
        return move;
    }
    move=random_move(move, dir, queen_index, player_black);
    execute_move(move,player_black.graph,player_black.current_queens);
    return move;  
}

/*this function returns the neighbor of a position pos in the grid */
int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
    return get_neighbor_gen(pos, dir, graph, player_black);
}

/*this function frees all allocated memory for the player from the start of the game intil the end
 it frees the graph and quuens positions*/
void finalize(){
    free(player_black.current_queens);
    free(player_black.other_queens);    
    gsl_spmatrix_uint_free(player_black.graph->t);
    free(player_black.graph);
}

