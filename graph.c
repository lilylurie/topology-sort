#include "graph.h"
graph *graph_init(int n)
{
    graph *g = (graph *)malloc(sizeof(graph));
    if (!g)
    {
        printf("Error. Memory wasn't allocated for graph");
        return NULL;
    }
    g->n = n;
    g->list = (List *)malloc(n * sizeof(List));
    if (!g->list)
    {
        printf("Error. Memory wasn't allocated for graph_list");
        return NULL;
    }
    for (int k = 0; k < n; k++)
    {
        g->list[k].number = k;
        g->list[k].head = NULL;
    }
    return g;
}
void add_arc(graph *g, int a, int b)
{
    if (!g->list[a].head)
    {
        LinkedNode *new_edge = (LinkedNode *)malloc(sizeof(struct LinkedNode));
        if (!new_edge)
        {
            printf("Error. Memory wasn't allocated for new_edge (line 50)");
            return;
        }
        new_edge->number_of_node = b;
        new_edge->next = NULL;
        g->list[a].head = new_edge;
        return;
    }
    LinkedNode *current = g->list[a].head;
    while (current->next)
    {
        if (current->number_of_node == b)
            return;
        current = current->next;
    }
    LinkedNode *new_edge = (LinkedNode *)malloc(sizeof(struct LinkedNode));
    if (!new_edge)
    {
        printf("Error. Memory wasn't allocated for new_edge (line 50)");
        return;
    }
    new_edge->number_of_node = b;
    new_edge->next = NULL;
    current->next = new_edge;
    return;
}
void add_edge(graph *g, int a, int b)
{
    add_arc(g, a, b);
    add_arc(g, b, a);
}
void del_arc(graph *g, int a, int b)
{
    if (g->list[a].head->number_of_node == b)
    {
        LinkedNode *j = g->list[a].head;
        g->list[a].head = g->list[a].head->next;
        free(j);
        return;
    }
    LinkedNode *current = g->list[a].head;
    while ((current->next) && (current->next->number_of_node != b))
        current = current->next;
    if (current->next)
    {
        LinkedNode *j = current->next;
        current->next = j->next;
        free(j);
        return;
    }
}
void del_edge(graph *g, int a, int b)
{
    del_arc(g, a, b);
    del_arc(g, b, a);
}
void free_edges(graph *g)
{
    for (int i = 0; i < g->n; i++)
    {
        if (g->list[i].head != NULL)
        {
            LinkedNode *current = g->list[i].head;
            while (current != NULL)
            {
                LinkedNode *j = current;
                current = current->next;
                free(j);
            }
        }
    }
}
void graph_free(graph *g)
{
    free_edges(g);
    free(g->list);
    free(g);
}
void graph_print(graph *g)
{
    if (!g)
    {
        printf("Graph doesn't exist");
        return;
    }
    for (int i = 0; i < g->n; i++)
    {
        printf("%d -> ", i);
        LinkedNode *current = g->list[i].head;
        while (current)
        {
            printf("%d -> ", current->number_of_node);
            current = current->next;
        }
        printf("NULL\n");
    }
}
bool find_arc(graph *g, int a, int b)
{
    if ((a < g->n) && (a >= 0) && (b < g->n) && (b >= 0))
    {
        if (g->list[a].head)
        {
            LinkedNode *current = g->list[a].head;
            while (current->next)
            {
                if (current->number_of_node == b)
                    return true;
                current = current->next;
            }
            if (current->number_of_node == b)
                return true;
        }
        else
            return false;
    }
    return false;
}