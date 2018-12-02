#ifndef TREE_H
#define TREE_H
#include "List.h"

typedef struct Node Node;
typedef struct Tree Tree;

struct Node
{
  List *key; 
  double pos;
  Node *sibling;
  Node *child;
  
};


struct Tree
{         
  Node *root;    
};

Tree *init_t();
Node *init_n();
void insert_sibling (Node *n, List *key);
void insert_child (Node *n, List *key);
List *get_node (Node *n);
void print_tree(Node *n);
int nb_children(Node *n);


#endif
