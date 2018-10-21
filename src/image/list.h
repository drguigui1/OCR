#ifndef LIST_H
#define LIST_H

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *next;
};

typedef struct List List;
struct List
{
  Element *first;
};

List *initialisation();
void insertion(List *list, int nvNombre);
void suppression(List *list);
void printlist(List *list, int jumpline);
void insertion_n(List *list, int new, int place);
int fromlist(List *list, int n);
void suppression(List *list);
void clean(List * list);
int size(List *l);
void copy(List *l1, List *l2);

#endif
