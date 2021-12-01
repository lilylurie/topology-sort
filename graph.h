#ifndef GRAPH_H_
#define GRAPH_H_
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedNode
{
    int number_of_node;
    struct LinkedNode *next;
} LinkedNode;
typedef struct List
{
    LinkedNode *head;
    int number;
    int visited;
} List;
typedef struct graph
{
    int n;
    List *list;
} graph;
graph *graph_init(int n);
void add_arc(graph *g, int a, int b);
void del_arc(graph *g, int a, int b);
void add_edge(graph *g, int a, int b);
void del_edge(graph *g, int a, int b);
void graph_print(graph *g);
void graph_free(graph *g);
bool find_arc(graph *g, int a, int b);

#endif
