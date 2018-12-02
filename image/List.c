#include<stdio.h>
#include<stdlib.h>

// LISTES CHAINEES
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

List *initialisation()
{
    List *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element-> value = -1;
    element->next = NULL;
    liste->first = element;

    return liste;
}

void insertion(List *liste, int nvNombre)
{
    /* Création du nouvel élément */
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->value = nvNombre;

    /* Insertion de l'élément au début de la liste */
    nouveau->next = liste->first;
    liste->first = nouveau;
}

void print_list(List *liste, int jumpline)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element *actuel = liste->first;

    while (actuel != NULL)
    {
        printf("%d -> ", actuel->value);
        actuel = actuel->next;
    }
    printf("NULL");

    if(jumpline)
      {
	printf("\n");
      }
}

int fromlist(List *liste, int n)
{
  int i = 0;
  if(liste == NULL)
    {
      exit(EXIT_FAILURE);
    }
  Element *actuel = liste -> first;

  while(actuel != NULL && i<n)
    {
      i++;
      actuel = actuel-> next;
    }
  if(actuel == NULL)
    {
      return -1;
    }
  return actuel-> value;
}

//not safe//
void insertion_n(List *list, int new, int place)
{
  int i = 0;
  insertion(list, -2);
  Element *curr = list -> first;
  
  for(i = 0; i < place && curr -> next -> value != -1; i++)
    {
      curr -> value = curr -> next -> value; 
      curr = curr -> next;
    }
  if(i == place && curr -> value != -1)
    curr -> value = new;
}


void suppression(List *list)
{
    if (list == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (list->first != NULL)
    {
        Element *aSupprimer = list->first;
        list->first = list->first->next;
        free(aSupprimer);
    }
}

//remove all doublons from a list
//create an other list and copy when new
void clean(List *list)
{
  //si liste nulle
  if(list == NULL)
    {
      exit(EXIT_FAILURE);
    }

  List *buffer = initialisation();
  int curr, curr2;
  int i =0;
  int j =0;
  int found = 0;
  
  while(fromlist(list, i) != -1)
    {
      //initialisation interne
      j = 0;
      found = 0;
      
      curr = fromlist(list, i);
      curr2 = fromlist(buffer,j);


      //bouclages
      while(curr2 != -1 && !found)
	{
	  if(curr != curr2)
	    {
	      j++;
	      curr2 = fromlist(buffer,j);
	    }
	  else
	    {
	      found = 1;
	    }
	}
      if(!found)
	{
	  insertion(buffer, curr);
	}
      i++;
    }
  *list = *buffer;
}

//return the size of the list, when reduced at -1, return 0 
int size(List *l)
{
  int i = 0;
  while(fromlist(l,i) != -1)
    {
      i++;
    }
  return i;
}

//copy values with independants lists
//l1 is the one to copy
void copy(List *l1, List *l2)
{
  int i = 0;
  while(fromlist(l1,i) !=-1)
    {
      insertion(l2, fromlist(l1,i));
      i++;
    }
}

//merge two lists
void merge(List *l1, List *l2)
{
  if(l1 -> first -> value == -1)
    {
      l1 -> first = l2 -> first;
    }
  else if(l2 -> first -> value != -1 )
    {
      Element *el = l1 -> first;
      
      while(el -> next && el -> next -> value != -1)
	{
	  el = el -> next;
	}
      el -> next = l2 -> first;
    }
}

void swap(List *l, int a, int b)
{
  Element *alpha = l -> first;
  Element *beta = l -> first;
  
  for(int i = 0; i< a; i++)
    {
      alpha = alpha -> next;
    }
  
  for(int i = 0; i< b; i++)
    {
      beta = beta -> next;
    }

  int curr = beta -> value;
  beta -> value  = alpha -> value;
  alpha -> value = curr;
}

void fract(List *l)
{
  while(fromlist(l,0) != -1)
    {
      suppression(l);
    }
}
