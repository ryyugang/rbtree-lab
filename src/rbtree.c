#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void) {
  printf ("----------new_rbtree in----------, \n");
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  if (p == NULL)
  {
    return NULL;
  }

  node_t *NIL_node = (node_t *)calloc(1, sizeof(node_t));

  if (NIL_node == NULL)
  {
    free(p);
    return NULL;
  }

  p -> nil = NIL_node;
  NIL_node -> color = RBTREE_BLACK;
  p -> root = NIL_node;
  
  return p;
}

void delete_node(rbtree *t, node_t *node) {
  printf ("----------delete_node in----------, \n");
  if (node == t -> nil)
  {
    return;
  }

  delete_node(t, node -> left);
  delete_node(t, node -> right);
  free(node);
  node = NULL;
}

void delete_rbtree(rbtree *t) {
  printf ("----------delete_rbtree in----------, \n");
  if (t == NULL)
  {
    return;
  }
  if (t -> root != t -> nil)
  {
    delete_node(t, t -> root);
  }
  
  free(t -> nil);
  t -> nil = NULL;
  free(t);
  t = NULL;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  printf ("----------rbtree_insert in----------, \n");
  node_t *z = (node_t *)calloc(1, sizeof(node_t));
  node_t *y = t -> nil;
  node_t *x = t -> root;

  while (x != t -> nil)
  {
    y = x;
    if (key < x -> key)
    {
      x = x -> left;
    }
    else // (key > x -> key)
    {
      x = x -> right;
    }
  }

  z -> parent = y;
  if (y == t -> nil)
  {
    t -> root = z;
  }
  else if (key < y -> key)
  {
    y -> left = z;
  }
  else // (key > y -> key)
  {
    y -> right = z;
  }
  z -> left = t -> nil;
  z -> right = t -> nil;
  z -> color = RBTREE_RED;
  z -> key = key;
  insert_fixup(t, z);

  return t->root;
}

void left_rotate_rbtree(rbtree *t, node_t *x) {
  printf ("----------left_rotate_rbtree in----------, \n");
  node_t *y;
  y = x -> right;
  x -> right = y -> left;
  if (y -> left != t -> nil)
  {
    (y -> left) -> parent = x;
  }

  y -> parent = x -> parent;

  if (x -> parent == t -> nil)
  {
    t -> root = y;
  }
  else // if (x -> parent != t -> nil)
  {
    if (x == (x -> parent) -> left)
    {
      (x -> parent) -> left = y;
    }

    if (x == (x -> parent) -> right)
    {
      (x -> parent) -> right = y;
    }
  }

  y -> left = x;
  x -> parent = y;

}

void right_rotate_rbtree(rbtree *t, node_t *x) {
  printf ("----------right_rotate_rbtree in----------, \n");
  node_t *y;
  y = x -> left;
  x -> left = y -> right;
  if (y -> right != t -> nil)
  {
    (y -> right) -> parent = x;
  }

  y -> parent = x -> parent;

  if (x -> parent == t -> nil)
  {
    t -> root = y;
  }
  else // if (x -> parent != t -> nil)
  {
    if (x == (x -> parent) -> right)
    {
      (x -> parent) -> right = y;
    }

    if (x == (x -> parent) -> left)
    {
      (x -> parent) -> left = y;
    }
  }

  y -> right = x;
  x -> parent = y;
}

void insert_fixup(rbtree *t, node_t *z) {
  printf ("----------insert_fixup in----------, \n");
  node_t *y;
  while (z -> parent -> color == RBTREE_RED)
  {
    if (z -> parent == z -> parent -> parent -> left)
    {
      y = z -> parent -> parent -> right;
      if (y -> color == RBTREE_RED)
      {
        z -> parent -> color = RBTREE_BLACK;
        y -> color = RBTREE_BLACK;
        z -> parent -> parent -> color = RBTREE_RED;
        z = z -> parent -> parent;
      }
      else // if (y -> color == RBTREE_BLACK)
      {
        if (z == z -> parent -> right)
        {
          z = z -> parent;
          left_rotate_rbtree(t, z);
        }
        z -> parent -> color = RBTREE_BLACK;
        z -> parent -> parent -> color = RBTREE_RED;
        right_rotate_rbtree(t, z -> parent -> parent);
      }
    }
    else // if (z -> parent == z -> parent -> parent -> right)
    {
      y = z -> parent -> parent -> left;
      if (y -> color == RBTREE_RED)
      {
        z -> parent -> color = RBTREE_BLACK;
        y -> color = RBTREE_BLACK;
        z -> parent -> parent -> color = RBTREE_RED;
        z = z -> parent -> parent;
      }
      else // if (y -> color == RBTREE_BLACK)
      {
        if (z == z -> parent -> left)
        {
          z = z -> parent;
          right_rotate_rbtree(t, z);
        }
        z -> parent -> color = RBTREE_BLACK;
        z -> parent -> parent -> color = RBTREE_RED;
        left_rotate_rbtree(t, z -> parent -> parent);
      }
    }
  }
  t -> root -> color = RBTREE_BLACK;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  printf ("----------rbtree_find in----------, \n");
  node_t *tmp = t -> root;

  while (tmp != t -> nil && tmp != NULL)
  {
    if (key < tmp -> key)
    {
      tmp = tmp -> left;
    }
    else if (key > tmp -> key)
    {
      tmp = tmp -> right;
    }
    else
    {
      return tmp;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  printf ("----------rbtree_min in----------, \n");
  node_t *tmp = t -> root;
  if (tmp == t -> nil)
  {
    return NULL;
  }

  while (tmp -> left != t -> nil)
  {
    tmp = tmp -> left;
  }

  return tmp;
}

node_t *rbtree_min_subtree(const rbtree *t, node_t *root) {
  printf ("----------rbtree_min_subtree in----------, \n");
  node_t *tmp = root;
  
  if (root == t -> nil)
  {
    return NULL;
  }

  while (tmp -> left != t -> nil)
  {
    tmp = tmp -> left;
  }

  return tmp;
}

node_t *rbtree_max(const rbtree *t) {
  printf ("----------rbtree_max in----------, \n");
  node_t *tmp = t -> root;

  if (tmp == t -> nil)
  {
    return NULL;
  }

  while (tmp -> right != t -> nil)
  {
    tmp = tmp -> right;
  }

  return tmp;
}

int rbtree_erase(rbtree *t, node_t *p) {
  printf ("----------rbtree_erase in----------, \n");

  if (p == NULL || p == t -> nil)
  {
    return -1;
  }
  node_t *x;
  node_t *y = p;
  color_t y_original_color = y -> color;
  
  if (p -> left == t -> nil)
  {
    x = p -> right;
    rbtree_transplant(t, p, p -> right);
  }
  else if (p -> right == t -> nil)
  {
    x = p -> left;
    rbtree_transplant(t, p, p -> left);
  }
  else //if (p -> right != t -> nil && p -> left != t -> nil)
  {
    y = rbtree_min_subtree(t, p -> right);
    y_original_color = y -> color;
    x = y -> right;

    if (y -> parent == p)
    {
      x -> parent = y;
    }
    else // if (y -> parent != p)
    {
      rbtree_transplant(t, y, y -> right);
      y -> right = p -> right;
      y -> right -> parent = y;
    }

    rbtree_transplant(t, p, y);
    y -> left = p -> left;
    y -> left -> parent = y;
    y -> color = p -> color;
  }
  
  if (y_original_color == RBTREE_BLACK)
  {
    delete_fixup(t, x);
  }
  
  if (t -> root == p)
  {
    t -> root = x;
  }

  free(p);

  return 0;
}

// 노드 삭제 시 하위 노드를 삭제된 노드 위치로 올리는 과정
// u는 삭제 노드, v는 u 노드의 하위 노드
void rbtree_transplant(rbtree *t, node_t *u, node_t *v) {
  printf ("----------rbtree_transplant in----------, \n");
  if (u -> parent == t -> nil)
  {
    t -> root = v;
  }
  else if (u == u -> parent -> left)
  {
    u -> parent -> left = v;
  }
  else // if (u == u -> parent -> right)
  {
    u -> parent -> right = v;
  }
  v -> parent = u -> parent;
}


void delete_fixup(rbtree *t, node_t *x) {
  printf ("----------delete_fixup in----------, \n");
  node_t *s;

  while (x != t -> root && x -> color == RBTREE_BLACK)
  {
    if (x == x -> parent -> left)
    {
      s = x -> parent -> right;
      if (s -> color == RBTREE_RED)
      {
        s -> color = RBTREE_BLACK;
        x -> parent -> color = RBTREE_RED;
        left_rotate_rbtree(t, x -> parent);
        s = x -> parent -> right;
      }
      if (s -> left -> color == RBTREE_BLACK && s -> right -> color == RBTREE_BLACK)
      {
        s -> color = RBTREE_RED;
        x = x -> parent;
      }
      else // if (s -> left -> color != RBTREE_BLACK or s -> right -> color =! RBTREE_BLACK)
      {
        if (s -> right -> color == RBTREE_BLACK)
        {
          s -> left -> color = RBTREE_BLACK;
          s -> color = RBTREE_RED;
          right_rotate_rbtree(t, s);
          s = x -> parent -> right;
        }
        s -> color = x -> parent -> color;
        x -> parent -> color = RBTREE_BLACK;
        s -> right -> color = RBTREE_BLACK;
        left_rotate_rbtree(t, x -> parent);
        x = t -> root;
      }
    }
    else // if (x == x -> parent -> right)
    {
      s = x -> parent -> left;
      if (s -> color == RBTREE_RED)
      {
        s -> color = RBTREE_BLACK;
        x -> parent -> color = RBTREE_RED;
        right_rotate_rbtree(t, x -> parent);
        s = x -> parent -> left;
      }
      if (s -> left -> color == RBTREE_BLACK && s -> right -> color == RBTREE_BLACK)
      {
        s -> color = RBTREE_RED;
        x = x -> parent;
      }
      else // if (s -> left -> color != RBTREE_BLACK or s -> right -> color != RBTREE_BLACK)
      {
        if (s -> left -> color == RBTREE_BLACK)
        {
          s -> right -> color = RBTREE_BLACK;
          s -> color = RBTREE_RED;
          left_rotate_rbtree(t, s);
          s = x -> parent -> left;
        }
        s -> color = x -> parent -> color;
        x -> parent -> color = RBTREE_BLACK;
        s -> left -> color = RBTREE_BLACK;
        right_rotate_rbtree(t, x -> parent);
        x = t -> root;
      }
    }
  }
  x -> color = RBTREE_BLACK;
}


int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  printf ("----------rbtree_to_array in----------, \n");
  node_t *tmp;

  for (int i=0; i < n; i++)
  {
    tmp = rbtree_min(t);
    if (tmp == NULL)
    {
      return -1;
    }
    arr[i] = tmp -> key;
    rbtree_erase(t, tmp);
  }
  return 0;
}

void rbtree_to_print(node_t *t, node_t *nil)
{
    if (t == nil)
    {
        printf("노드 바닥이에용\n");
        return;
    }
    printf("key = %d, color = %d \n", t->key, t->color);
    rbtree_to_print(t->left, nil);
    rbtree_to_print(t->right, nil);
}