#include<stdio.h>
#include<stdlib.h>
#include <err.h>
#include "List.h"


typedef struct Node Node;
typedef struct Tree Tree;

//Structure d'un noeud
struct Node
{
  List *key; //Clé du noeud (liste d'int)
  double pos; 
  Node *sibling;
  Node *child;
};

// Structure arbre binaire
struct Tree
{
  Node *root; //Pointeur noeud racine; 
};

// Initialisation arbre
Tree *init_t ()
{
  Tree *t = malloc(sizeof(*t));
  Node *N = malloc(sizeof(*N));
  if (t == NULL || N == NULL)
    errx(1, "not initialised t or N in init_t");
  
  List *l = initialisation();
  
  N->key = l;
  N->sibling = NULL;
  N->child = NULL;
  N -> pos = -1;
  t->root = N;
  return t;
}

//Initialisation noeud
Node *init_n ()
{
  Node *n = malloc(sizeof(*n));
  if (n == NULL)
    errx(1, "n failed init in init_n\n");
  n -> key = initialisation();
  n -> child = NULL;
  n -> sibling = NULL;
  n -> pos = -1;
  return n;
}



// Insertion sibling
void insert_sibling (Node *n, List *key)
{
  Node *sibling = init_n(key);
  if (n -> sibling != NULL)
    errx(1,"yet a sibling");
  //else
    n->sibling = sibling;
}



// Insertion child
void insert_child (Node *n, List *key)
{
  if (n-> child != NULL)
    errx(1,"yet a child");
  
  n -> child = init_n(key);

}



//Récupère la key du noeud actuel
List *get_node (Node *n)
{
	return n->key;
}


//Affiche l'arbre
/*void _print_tree(Node *n)
{
  printf("(");;
  print_list(n->key, 0);
  if (n -> child != NULL)
    {
      Node *c = n->child;
      while (c != NULL)
	{
	  _print_tree(c);
	  c = c->sibling;
	}
    }
  printf(")");
  }*/

void _print_tree(Node *t) {
  if (t)
    {
      print_list( t-> key, 0);
      if(t -> sibling)
	printf(" |S: ");
      _print_tree(t -> sibling);
      if(t -> child)
	printf(" |C: ");
      _print_tree(t -> child);
    }
}

void print_tree(Node *n)
{
  _print_tree(n);
  printf("\n");
}


//return number of child
int nb_children(Node *n)
{
  if(n == NULL)
    {
      return 0;
    }
  Node *curr = n;
  int i =1 ;
  while(curr -> sibling)
    {
      i++;
      curr = curr -> sibling;
    }
  return i;
}
