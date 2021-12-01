#include "graph.h"
#include "stack.h"
#include <stdbool.h>
typedef struct top_sort_list
{
    int num;
    struct top_sort_list *next;
} top_sort_list;

void push_sort_list(top_sort_list **result, int num)
{
    top_sort_list *new = (top_sort_list *)malloc(sizeof(top_sort_list));
    // top_sort_el *new_el = (top_sort_el *)malloc(sizeof(top_sort_el));
    // new_el->list = l;
    new->num = num;
    new->next = (*result);
    (*result) = new;
    return;
}
void print_top_sort_list(top_sort_list *result)
{
    while (result)
    {
        printf("%d ->", result->num);
        result = result->next;
    }
    if (result == NULL)
        printf(" NULL");
    printf("\n");
}
void free_top_sort_list(top_sort_list *result)
{
    while (result)
    {
        top_sort_list *j = result;
        result = result->next;
        free(j);
    }
}
int dfs(int number_of_start_list, graph *g, top_sort_list **result)
{
    stack *stack_s = get_stack();
    if (!stack_s)
    {
        printf("dfs: memory wasn't allocated for stack\n");
        return 0;
    }
    if (!push_stack(stack_s, &g->list[number_of_start_list]))
    {
        printf("dfs: Push_stack failed\n");
        return 0;
    }
    g->list[number_of_start_list].visited = 1;
    while (stack_s->head)
    {
        stack_s->head->element->visited = 1;
        List *changes = stack_s->head->element;
        LinkedNode *current = stack_s->head->element->head;
        if (!current)
        {
            stack_s->head->element->visited = -1;
            push_sort_list(result, stack_s->head->element->number); //&g->list[stack_s->head->element->number]);
            pop_stack(stack_s, NULL);
        }
        else
        {
            while (current)
            {
                if (g->list[current->number_of_node].visited == 1)
                {
                    return 0;
                }
                if (g->list[current->number_of_node].visited != -1)
                    if (!push_stack(stack_s, &g->list[current->number_of_node]))
                    {
                        printf("dfs: Push_stack failed\n");
                        return 0;
                    }
                // g->list[current->number_of_node].visited++;
                current = current->next;
            }
            if (changes == stack_s->head->element)
            {
                stack_s->head->element->visited = -1;
                push_sort_list(result, stack_s->head->element->number); //&g->list[stack_s->head->element->number]);
                pop_stack(stack_s, NULL);
            }
        }
    }
    return 1;
}

top_sort_list *make_topology_sort(graph *g)
{
    top_sort_list *result = NULL;
    for (int i = 0; i < g->n; i++)
    {
        if (g->list[i].visited != -1)
        {
            if (!dfs(i, g, &result))
            {
                printf("make_topology_sort: toppology sort doesn't exist\n");
                free_top_sort_list(result);
                return NULL;
            }
        }
    }
    return result;
}

graph *make_graph()
{
    graph *g = graph_init(3);
    add_arc(g, 0, 1);
    add_arc(g, 1, 2);
    //add_arc(g, 1, 0);
    // add_arc(g, 3, 5);
    // add_arc(g, 5, 4);
    // add_arc(g, 4, 1);
    // add_arc(g, 1, 2);
    return g;
}

bool uniq_top_sort(graph *g, top_sort_list *g_top)
{
    top_sort_list *mom_shark = g_top;
    if (mom_shark)
    {
        while (mom_shark->next)
        {
            if (!find_arc(g, mom_shark->num, mom_shark->next->num))
                return false;
            mom_shark = mom_shark->next;
        }
    }
    else
    {
        printf("uniq_top_sort: Topology sort desn't exist\n");
        return false;
    }
    return true;
}

int main()
{
    graph *g = make_graph();
    top_sort_list *g_top = make_topology_sort(g);
    if (g_top)
    {
        print_top_sort_list(g_top);
        if (uniq_top_sort(g, g_top))
            printf("Сортировка единственна\n");
        else
            printf("Сортировка не единственна\n");
    }
    return 0;
}