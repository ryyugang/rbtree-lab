#include "stack.h"

void delete_node(rbtree *t, node_t *node) {
    printf("----------delete_node in----------, \n");
    if (node == t->nil) {
        return;
    }

    Stack stack;
    initialize_stack(&stack);
    push(&stack, node);

    while (!is_empty(&stack)) {
        node_t *current_node = pop(&stack);
        if (current_node->left != t->nil) {
            push(&stack, current_node->left);
        }
        if (current_node->right != t->nil) {
            push(&stack, current_node->right);
        }
        free(current_node);
    }
}

void push(Stack *stack, node_t *node) {
    StackNode *tmp;
    tmp = malloc(sizeof(StackNode));

    if (tmp == NULL)
    {
        return;
    }
    tmp -> data = node;

    if (stack -> top == NULL)
    {
        stack -> top = tmp;
        tmp -> next = NULL;
    }
    else
    {
        tmp -> next = stack -> top;
        stack -> top = tmp;
    }
}


node_t *pop(Stack *s) {
    StackNode *tmp, *t;
    node_t *ptr;
    ptr = NULL;

    t = s -> top;
    if (t != NULL)
    {
        tmp = t -> next;
        ptr = t -> data;

        s -> top = tmp;
        free(t);
        t = NULL;
    }
    return ptr;
}


int isEmpty(Stack *s){
    if (s -> top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}