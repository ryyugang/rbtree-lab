#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

typedef struct _stackNode {
    node_t *data;
    struct _stackNode *next;
} StackNode;

typedef struct _stack {
    StackNode *top;
} Stack;

void postOrderIterativeS2(node_t *root);

void push(Stack *stack, node_t *node);
node_t *pop(Stack *s);
int isEmpty(Stack *s);
