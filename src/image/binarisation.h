#ifndef BINARISATION_H
#define BINARISATION_H
#include "../utils/Matrix.h"
#include "../utils/list.h"
#include "../utils/tree.h"

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
void print_Tree(Node *n);
Tree *binarisation(Matrix array);

#endif
