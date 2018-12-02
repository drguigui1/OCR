#ifndef BINARISATION_H
#define BINARISATION_H

#include "Tree.h"
#include "List.h"
#include "Matrix.h"

typedef struct Vector2 Vector2;
struct Vector2
{
    int x;
    int y;
};

void neighbours(Matrix array, List *actual, List *next, List *contrast, double base);
void propa(Matrix array, List *curr, List *next, List *contrast);
void build_woods(Matrix array, Node *father);
void buildTree(Matrix array, Vector2 initpos, Tree *T);
Tree *binarisation(Matrix array);

void alpha();

List *get_char(Matrix array,double pos);
void blankless(Matrix array, List *list);

void white_holes(Node *n, double base, Matrix array);
void _remove_holes(Node *n, Matrix array, double color);
void remove_holes(Tree *t, Matrix array);


#endif
