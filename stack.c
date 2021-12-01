#include "stack.h"
stack * get_stack(){
    stack * s = (stack *)malloc(sizeof(stack));
    if (!s){
        printf("Memory wasn't allocated for stack\n");
        return NULL;
    }
    s->head = NULL;
    return s;
}
int  push_stack(stack * s ,STACKNODE_TYPE  new_el){
    stack_node * new_element = (stack_node *)malloc(sizeof(stack_node));
    if (!new_element)
        return 0;
    new_element->element = new_el;
    new_element->next = s->head;
    s->head = new_element;
    return 1;  
}
int  pop_stack(stack *s, STACKNODE_TYPE * del_el){
    if (!s->head){
        printf("Stack is empty\n");
        return 0; 
    }
    stack_node * f = s->head ;
    if (del_el)
        (*del_el) = f->element;
    s->head = s->head->next; 
    free(f);
    return 1;   
}