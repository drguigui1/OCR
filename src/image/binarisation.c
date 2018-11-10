#include <stdio.h>
#include "Matrix.h"
#include "list.h"
#include "tree.h"

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


void neighbours(Matrix array,List *actual,List *next,List *contrast,double base)
{
  double cell = 0;
  
  //get coor
  //take number of columns
  int L = array.columns;
  
  Vector2 pos;
  pos.x = fromlist(actual,0)/L;
  pos.y = fromlist(actual,0)%L;
  suppression(actual);

  

  // printf("x: %d, y: %d\n",pos.x, pos.y);

 
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
  int boucle = 1;
  double base = *(array.pt + fromlist(curr,0));
  
  while(boucle)
    {
      while(fromlist(curr,0) != -1)
	{
	  //printf("boucle \n");
	  neighbours(array, curr, next, contrast,base);
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




void build_woods(Matrix array, Node *father)
{
  List *init_contrast = initialisation();
  copy(father -> key,init_contrast);
  
  //can be usefull in presentation   
  /* printf("father -> key\n");
     printlist(father -> key,1);*/
  
  if(fromlist(init_contrast,0) != -1)
    {
      //initialisations
      father -> child = init_n(initialisation()); //ERROR CORRECT

      Node *son = father -> child; //position of son
      List *curr = initialisation();
      List *next = initialisation();
      List *after_contrast = initialisation();
      
      insertion(curr, fromlist(init_contrast,0)); //1st coor of propa
      
      propa(array, curr, next, after_contrast); // propagation
      clean (after_contrast); //remove twins


      //can be usefull in oral
      /*
      printf("after_contrast\n");
      printlist(after_contrast,1);*/

      copy(after_contrast, son -> key);//attribution list
      
      
      build_woods(array, son); //retry on son
      blankless(array, init_contrast); // cleaning the useless positions

      
      
       while(fromlist(init_contrast,0) != -1)
	{
	  son -> sibling  = init_n(initialisation()); //CORRECT ERROR
	  son = son -> sibling; //update current
	  insertion(curr,fromlist(init_contrast,0)); //1st coor of propa
	  propa(array, curr, next, son -> key); //propagation, filling son's key
	  blankless(array,init_contrast); //cleqning contrast list
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

  double column = array.columns;
  
  //first propagation
  insertion(curr,initpos.x*column+initpos.y);
  propa(array,curr,next,contrast);

  //creating node
  Node *father = T -> root;
  clean(contrast);
  
  copy(contrast, father -> key);
  
  build_woods(array, father);
}

//-----------------------------------------------------------//
//-------------------Print tree------------------------------//
//-----------------------------------------------------------//

void print_Tree(Node *n)
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

Tree *binarisation(Matrix array)
{
  Vector2 zero; zero.x = 0; zero.y = 0;
  Tree *T = init_t();
  Matrix work_on = copy_matrix(array); //create new matrix that can be destroyed

  
  buildTree(work_on, zero, T);
  return T;
      
}
