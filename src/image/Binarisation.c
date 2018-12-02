#include <stdio.h>
#include "Matrix.h"
#include "List.h"
#include "Tree.h"
#include <stdlib.h>

typedef struct Vector2 Vector2;
struct Vector2
{
  int x;
  int y;
};


//--------------------------------------------------------------------//
//--------------------------NEIGHBOURS--------------------------------//
//--------------------------------------------------------------------//

//fill the list neighbours of the top of actual list
//_in next if no contrast from top of list
//_ in contrast if so
//flag of the visited cell: -1


void neighbours(Matrix array, List *actual, List *next, List *contrast, double base)
{

  
  
  double cell = 0;
  
  //get coor
  //take number of columns
  int L = array.columns;
  //int i = 0;
  
  Vector2 pos;
  pos.x = fromlist(actual,0)/L;
  pos.y = fromlist(actual,0)%L;
  suppression(actual);

  /*for(i = pos.x+pos.y*L; i<array.rows*array.columns && *(array.pt + i) != base; i++)
    {
      insertion(next, i);
      *(array.pt + i) = -1;
    }

  // printf("x: %d, y: %d\n",pos.x, pos.y);

  pos.x = i % L;
  pos.y = i / L;*/
  
  //up
  if(pos.x > 0)
    {
      cell = *(array.pt + (pos.x-1)*array.columns + pos.y);
      if(cell == base)
	{
	  insertion(next, (pos.x-1)*L+pos.y);
	}
      else if(cell != -1)
	{
	  insertion(contrast, (pos.x-1)*L + pos.y);
	}
    }
  //down
  if(pos.x < array.rows-1)
    {
      cell = *(array.pt + (pos.x+1)*array.columns + pos.y);
      if(cell == base)
	{
	  insertion(next, (pos.x+1)*L + pos.y);
	}
      else if(cell != -1)
	{
	  insertion(contrast, (pos.x+1)*L+ pos.y);
	}
    }
  //left
  if(pos.y > 0)
    {
      cell = *(array.pt + (pos.x)*array.columns + pos.y-1);
      if(cell == base)
	{
	  insertion(next, pos.x*L +pos.y-1);
	}
      else if(cell != -1)
	{
	  insertion(contrast, pos.x*L + pos.y-1);
	}
    }
  //right
  if(pos.y < array.columns-1)
    {
      cell = *(array.pt + (pos.x)*array.columns + pos.y+1);
      if(cell == base)
	{
	  insertion(next, pos.x*L + pos.y+1);
	}
      else if(cell != -1)
	{
	  insertion(contrast, pos.x*L + pos.y+1);
	}
    }

  //put a mark on the cell;
   *(array.pt + (pos.x)*array.columns + pos.y) = -1;
}

//-----------------------------------------------------------//
//-------------------blankless-------------------------------//
//-----------------------------------------------------------//

//remove the cordonates of an array from a list that are at -1

void blankless(Matrix array, List *list)
{
  List *new = initialisation();
  int i =0;
  while(fromlist(list,i) != -1)
    {
      if(*(array.pt + fromlist(list,i)) != -1)
	{
	  insertion(new, fromlist(list,i));
	}
      i++;
    }
  *list = *new;
}

//-----------------------------------------------------------//
//--------------------Propa----------------------------------//
//-----------------------------------------------------------//

//return contast from the 1st cell of actual
//filling list contrast
//comparaison value: 1st value of current;


void propa(Matrix array, List *curr, List *next, List *contrast)
{
  //List *link = initialisation();

  
  
  int boucle = 1;
  double base = *(array.pt + fromlist(curr,0));
  
  while(boucle)
    {
      //printf("turn \n");
      
      while(fromlist(curr,0) != -1)
	{
	  
	  neighbours(array, curr, next, contrast,base);
	  //clean(next);
	  printf(".");
	}
      if(fromlist(next,0) == -1)
	{
	  boucle = 0;
	}
      else
	{
	  curr = next;
	  next = initialisation();
	}
    }
}

//-----------------------------------------------------------//
//--------------------Get-CHAR-------------------------------//
//-----------------------------------------------------------//

List *get_char(Matrix array, double pos)
{
  List *car = initialisation(); //list returned at the end

  List *init = initialisation();
  List *next = initialisation();
  List *contrast = initialisation();

  insertion(init, pos);
  insertion(car, pos);
 
  double base = *(array.pt + (int)pos);
  
  while(fromlist(init,0) != -1)
    {
      neighbours(array, init , next, contrast, base); //fuite memoire ??
      clean(next);
      init = next;
      List *next2 = initialisation();
      copy(next, next2);
      merge(car, next2);
    }

  clean(car);
  return car;
}

//-----------------------------------------------------------//
//---------------------BUILD-WOODS---------------------------//
//-----------------------------------------------------------//

void build_woods(Matrix array, Node *father)
{

  
  List *init_contrast = initialisation();
  copy(father -> key, init_contrast);

  
  if(fromlist(init_contrast,0) != -1)
    {

      
      //initialisations
      father -> child = init_n(); //ERROR CORRECT

      Node *son = father -> child; //position of son
      
      List *curr = initialisation();
      List *next = initialisation();
      List *after_contrast = initialisation();
      
      insertion(curr, fromlist(init_contrast,0)); //1st coor of propa
      son -> pos = fromlist(init_contrast,0); //coor of propa on son node

      propa(array, curr, next, after_contrast); // propagation
      clean(after_contrast); //remove twins

      copy(after_contrast, son -> key);//attribution list
      
      build_woods(array, son); //retry on son
      blankless(array, init_contrast); // cleaning the useless positions

       while(fromlist(init_contrast,0) != -1)
	{
	  son -> sibling  = init_n(); //CORRECT ERROR
	  son = son -> sibling; //update current
	  son -> pos = fromlist(init_contrast, 0);
	  insertion(curr,fromlist(init_contrast,0)); //1st coor of propa
	  propa(array, curr, next, son -> key); //propagation, filling son's key
	  blankless(array,init_contrast); //cleaning contrast list
	  build_woods(array, son); //retry on son
	  }
    }
}

//-----------------------------------------------------------//
//--------------------buildTree------------------------------//
//-----------------------------------------------------------//

//build a general tree from the contrast of an array
void buildTree(Matrix array, Vector2 initpos, Tree *T)
{
  List *curr = initialisation();
  List *next = initialisation();
  List *contrast = initialisation();
  //List *contrast2 = initialisation();

  double column = array.columns;
  
  //first propagation
  insertion(curr,initpos.x*column+initpos.y);
  propa(array,curr,next,contrast);

  //creating node
  Node *father = T -> root;
  T -> root -> pos = initpos.y*column + initpos.x;
  
  clean(contrast);
  
  copy(contrast, father -> key);

  build_woods(array, father);
}

//-----------------------------------------------//
//--------------------WHITE-HOLE-----------------//
//-----------------------------------------------//
void white_holes(Node *n, double base, Matrix array)
{
  if(n && n -> child && !n -> child -> child)
    {

      if(!n -> child -> sibling &&  *(array.pt + (int)n -> child -> pos) == base)
	{
	  //printf("no sibling\n");
	  free(n->child);
	  n-> child = NULL;
	}
      else
	if(
	   *(array.pt + (int)n-> child -> pos) == base
	   && *(array.pt + (int)n -> child -> sibling -> pos) == base
	   && ! n -> child -> sibling -> sibling
	   && ! n -> child -> sibling -> child)
	  {
	    //printf("with sibling\n");
	   free(n -> child);
	   n -> child = NULL;
	}
    }
}

//-----------------------------------------------//
//-------------------REMOVE-HOLES----------------//
//-----------------------------------------------//
void _remove_holes(Node *n, Matrix array, double color)
{
  if(n)
    {
      white_holes(n,color, array);
      color = *(array.pt + (int)n -> pos);
      _remove_holes(n -> sibling, array, color);
      _remove_holes(n-> child, array, color);
    }
}

void remove_holes(Tree *t, Matrix array)
{
  double color = *(array.pt + (int)t -> root -> pos);
  _remove_holes(t -> root -> child, array, color);
  _remove_holes(t -> root -> sibling, array, color);
}

//-----------------------------------------------------------//
//-------------------Binarisation----------------------------//
//-----------------------------------------------------------//
Tree *binarisation(Matrix array)
{
  Vector2 zero; zero.x = 0; zero.y = 0;
  Tree *T = init_t();
  
  Matrix work_on = copy_Matrix(array); //create new matrix that can be destroyed
  //printf("turn \n");
  buildTree(work_on, zero, T);
  
  remove_holes(T,array);
  free(work_on.pt);
  return T;
}


//-----------------------------------------------------------//
//-------------------test------------------------------------//
//-----------------------------------------------------------//
void alpha()
{
  /*printf("alpha\n");
  Tree *t = init_t();
  Node *n = init_n();
  t -> root -> child = init_n();
  t -> root -> child -> child = init_n();
  printf("is null: %i\n",t -> root -> child -> child == NULL);
  print_tree(t -> root);
  printf("\n");*/
  printf("alpha");
}
