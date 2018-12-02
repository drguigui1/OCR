#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Tree.h"
#include "Binarisation.h"

//-----------------------------------------------//
//--------------------CENTER---------------------//
//-----------------------------------------------//

//move the list to an interval closer to zero.
// list -> list
//need the number of cols

List *center(List *l, int cols)
{
  Element *curr = l -> first;
  
  int min_x = l -> first -> value % cols;
  int min_y = l -> first -> value / cols;

  int x = min_x;
  int y = min_y;

  while(curr -> value != -1) //find the minimum position
    {
      double pos = curr -> value;
      x = (int)pos % cols;
      y = (int)pos / cols;

      if(x < min_x) //check les x
	{
	  min_x = x;
	}
      if(y < min_y) //check les y
	{
	  min_y = y;
	}
      curr = curr -> next;
    }
  
  curr = l-> first;

  double min = min_y*cols +min_x;
  
  while(curr -> value != -1) //move all the values
    {
      curr -> value -= min;
      curr = curr -> next;
    }
  return l;
}

//-----------------------------------------------//
//------------------MIN-POS----------------------//
//-----------------------------------------------//

double min_pos(List *l, int cols)
{
  if(l-> first -> value == -1)
    return -1;
  
  Element *curr = l -> first;
  
  int min_x = l -> first -> value % cols;
  int min_y = l -> first -> value / cols;

  int x = min_x;
  int y = min_y;
  
  while(curr -> value != -1) //find the minimum position
    {
      double pos = curr -> value;
      x = (int)pos % cols;
      y = (int)pos / cols;
      
      if(x < min_x) //check les x
	{
	  min_x = x;
	}
      if(y < min_y) //check les y
	{
	  min_y = y;
	}
      curr = curr -> next;
    }
  
  return min_y*cols + min_x;
}

//-----------------------------------------------//
//------------------MAX-POS----------------------//
//-----------------------------------------------//

double max_pos(List *l, int cols)
{
  if(l-> first -> value == -1)
    return -1;
  
  Element *curr = l -> first;
  
  int max_x = l -> first -> value % cols;
  int max_y = l -> first -> value / cols;

  int x = max_x;
  int y = max_y;
  
  while(curr -> value != -1) //find the minimum position
    {
      double pos = curr -> value;
      x = (int)pos % cols;
      y = (int)pos / cols;
      
      if(x > max_x) //check les x
	{
	  max_x = x;
	}
      if(y > max_y) //check les y
	{
	  max_y = y;
	}
      curr = curr -> next;
    }
  
  return max_y*cols + max_x;
}

//-----------------------------------------------//
//--------------------COLLECT--------------------//
//-----------------------------------------------//

//return list of contrast in tree
void _collect_l(Node *n, List *l)
{
  if(n && n -> child == NULL && n -> sibling == NULL)
    {
      merge(l, n-> key);
      insertion(l , -3);
    }
  else if(n && n-> child == NULL)
    {
      merge(l, n-> key);
      insertion(l,-2);
      _collect_l(n-> sibling, l);
    }
  else if(n)
    {
      _collect_l( n-> sibling ,l);
      _collect_l(n -> child, l);
    }
}

List *collect_l(Tree *t)
{
  List *l= initialisation();
  Node *n = t -> root;
  _collect_l(n,l);
  return l;
}


//return list of calls of propagations
void _collect_pos(Node *n, List *l)
{
  if(n && n -> child == NULL && n -> sibling == NULL)
    {
      insertion(l,n -> pos);
      insertion(l , -2);
    }
  else if(n && n-> child == NULL)
    {
      insertion(l, n-> pos);
      _collect_pos(n-> sibling, l);
    }
  else if(n)
    {
      _collect_pos( n-> sibling ,l);
      _collect_pos(n -> child, l);
    }
}

List *collect_pos(Tree *t)
{
  Node *n = t -> root;
  List *l= initialisation();
  _collect_pos(n,l);
  return l;
}

//-----------------------------------------------//
//----------------CONVERTIONS--------------------//
//-----------------------------------------------//

//transform a list of coor to an array of cols = 1
Matrix coor_to_matrix(List *l, int init_cols)
{
  int max = max_pos(l,init_cols);
  int max_x = max%init_cols;
  int max_y = max/init_cols;

  //printf("max_x: %i\n",max_x+1);
  //printf("max_y: %i\n",max_y+1);
  //printf("total size: %i\n", ((max_x+1)*(max_y+1))-1);
  
  Matrix array = init_matrix_zero((max_x+1),(max_y+1));
  int i = 0, n = size(l);
  while(i <  n)
    {
      int pos = (int)fromlist(l,i);
      *(array.pt + pos % init_cols + (pos / init_cols * (max_x+1))) = 1;
      i++;
    }

  return array;
}

//convert a list to a matrix n*1
Matrix list_to_matrix(List *l)
{
  int n = size(l), i = 0;
  Matrix array = init_matrix_zero(n,1);

  for(i = 0; i<n; i++)
    {
      *(array.pt + i) = fromlist(l,i);
    }
  
  return array;
}

//transform a list to a column array;
List *matrix_to_list(Matrix array)
{
  List *l = initialisation();
  for(int i = array.columns * array.rows -1; i > -1; i--)
    {
      insertion(l, *(array.pt + i));
    }
  return l;
}

//return a matrix with the contrast listed at 1
Matrix array_of_contrast(List *l, int rows, int cols)
{
  Matrix array = init_matrix_zero(rows*cols, 1);
  array.columns = cols;
  array.rows = rows;

  int i = 0;
  double x = fromlist(l,i);
  while(x != -1)
    {
      if(x > -1)
	{
	  *(array.pt + (int)x) = 1;
	}
      else
	{
	  *(array.pt + (int)x) = x;
	}
      i++;
      x = fromlist(l,i);
    }
  return array;
}

//-----------------------------------------------//
//----------------MEDIUM-------------------------//
//-----------------------------------------------//
int medium(List *l)
{
  int i = 0, n = size(l);
  double count = 0;
  for(i = 0; i< n; i++)
    {
      count += fromlist(l,i);
    }
  return (int)count/n;
}


//-----------------------------------------------//
//-------------------RESIZE----------------------//
//-----------------------------------------------//

//resize a matrix to a superior size matrix;
Matrix resize(Matrix array,int rows, int columns)
{
  Matrix final = init_matrix_zero(rows,columns);
  for(int y = 0; y < array.rows; y++)
    {
      for(int x = 0; x < array.columns; x++)
	{
	  *(final.pt + y*columns + x) = *(array.pt + y*array.columns + x);
	}
    }
  return final;
}

//-----------------------------------------------//
//----------------ANALYSE------------------------//
//-----------------------------------------------//

Matrix analyse(Tree *t, Matrix array)
{
  
  List *pos = collect_pos(t);
  List *chars = initialisation();
  Matrix copy = copy_Matrix(array);
  int i = 0;
  
  while(fromlist(pos,i) != -1)
    {
      if(fromlist(pos,i) < -1)
	{
	  insertion(chars,fromlist(pos,i));
	  i++;
	}
      else
	{
	  
	  
	  List *curr = get_char(copy, fromlist(pos,i));
	  int mid = medium(curr);
	  
	  center(curr, copy.columns);

	  printf("char:\n");
	  print_list(curr,1);
	  
	  Matrix m = resize(coor_to_matrix(curr,array.columns),10,10);

	  curr = matrix_to_list(m);
	  
	  insertion(curr,mid);
	  
	  merge(chars, curr);
	  
	  i++;
	  
	  free(m.pt);
	}
    }

  printf("\n");

  return list_to_matrix(chars);
}




//-----------------------------------------------//
//--------------------TEST-----------------------//
//-----------------------------------------------//


void test()
{
  
}

