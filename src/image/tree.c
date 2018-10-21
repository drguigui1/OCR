#include<stdio.h>
#include<stdlib.h>
#include <err.h>
#include "list.h"


typedef struct Node Node;
typedef struct Tree Tree;

//Structure d'un noeud
struct Node
{
	List *key; //Clé du noeud (liste d'int)
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
	t->root = N;
	return t;
}

//Initialisation noeud
Node *init_n (List *key)
{
	Node *n = malloc(sizeof(*n));
	if (n == NULL)
	  errx(1, "n failed init in init_n");
	n->key = key;
	n->child = NULL;
	n->sibling = NULL;
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
void print_tree(Node *n)
{
	printf("(");;
	printlist(n->key, 0);
	if (n->child != NULL)
	{
		Node *c = n->child;
		while (c != NULL)
		{
			print_tree(c);
			c = c->sibling;
		}
	}
	printf(")");

}
