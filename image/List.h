#ifndef LIST_H
#define LIST_H

typedef struct Element Element;
struct Element
{
    int value;
    Element *next;
};

typedef struct List List;
struct List
{
  Element *first;
};

List *initialisation();

void insertion(List *list, int nvNombre);
void insertion_n(List *list, int new, int place);
void suppression(List *list);
void print_list(List *list, int jumpline);
int fromlist(List *list, int n);
void clean(List * list);
int size(List *l);
void copy(List *l1, List *l2);
void merge(List *l1, List *l2);
void swap(List *l, int a, int b);
void fract(List *l);

#endif
