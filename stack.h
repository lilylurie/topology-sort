#ifndef STACK_H_
#define STACK_H_
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef STACKNODE_TYPE
#define STACKNODE_TYPE \
List * 
#endif


typedef struct stack_node{
    STACKNODE_TYPE  element;
    struct stack_node * next; 
}stack_node;
typedef struct stack{
    stack_node * head;
}stack;
stack * get_stack();
int  push_stack(stack * s ,STACKNODE_TYPE  new_el);
int pop_stack(stack *s, STACKNODE_TYPE * del_el);


#endif