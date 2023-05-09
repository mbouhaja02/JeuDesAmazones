
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../src/graph.h"
#include "../src/server_functions.h"
#include <assert.h>

extern struct graph_t * initialize_graph(unsigned int length);
extern void free_graph(struct graph_t* g);
extern void make_graph(struct graph_t * g, unsigned int m ,char s );

void test_graph_table(void){
    printf("-----Started Testing graph_table---------- \n");
    struct graph_t* graph=initialize_graph(4);
    make_graph(graph,4,'c');
    int *t=graph_table(graph);
    for(int i=0;i<9;i++){
        assert(t[0]==0);
    }
    free(t);
    free_graph(graph);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    printf("-----Finished Testing graph_table---------- \n");

}

void test_table(void){
    printf("-----Started Testing table---------- \n");
    struct graph_t* graph=initialize_graph(3);
    make_graph(graph,3,'c');
    int *t=graph_table(graph);

    unsigned int a[1]={0};
    unsigned int b[1]={8};
    unsigned int *queens[NUM_PLAYERS]={a,b};
    table(queens,t,1);
    assert(t[0]==1);
    assert(t[8]==2);
    assert(t[3]==0);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    free(t);
    free_graph(graph);
    printf("-----FinishedTesting table---------- \n");
}

void start_next(void){
    printf("-----Started Testing strat_next_players---------- \n");
    assert(start_player()>=0);
    assert(start_player()<=1);
    printf("\033[32mTest 1/2 PASSED\033[0m\n");

    int player=BLACK;
    assert(next_player(player)==WHITE);
    assert(next_player(WHITE)==BLACK);
    printf("\033[32mTest 2/2 PASSED\033[0m\n");
    printf("-----Finished Testing strat_next_players---------- \n");

}

void test_copy_queens(void){
    printf("-----Started Testing copy_queens---------- \n");
    unsigned int t[2]={2,4};
    unsigned int h[2]={1,3};
    unsigned int *queens[2]={t, h};
    unsigned int *queens1[2]={allouer_table(2), allouer_table(2)};
    queens_copy(queens, queens1, 2);
    assert(queens1[0][0]==queens[0][0]);
    assert(queens1[0][1]==queens[0][1]);
    assert(queens1[1][0]==queens[1][0]);
    assert(queens1[1][1]==queens[1][1]);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    free(queens1[0]);
    free(queens1[1]);
    printf("-----Finished Testing copy_queens---------- \n");

}

void test_display(void){
     struct graph_t* graph=initialize_graph(4);
    make_graph(graph,4,'c');
    struct graph_t *graph2=graph_cpy(graph);
     unsigned int t[2]={2,4};
    unsigned int h[2]={1,3};
    unsigned int *queens[2]={t, h};
    sdl_display(graph2,queens,2,4);
    printf("\n");
    display(graph,queens,2);
    free_graph(graph);
    free_graph(graph2);

}
