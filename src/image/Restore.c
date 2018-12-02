#include <stdio.h>
#include "Matrix.h"
#include "List.h"
#include "Tree.h"


void bubble_sort_cols(List *l, int cols)
{
  int i = 0, n = size(l);
  for(i = n-1; i>0; i--)
    {
      for(int j = 0; j<i; j++)
	{
	  if(fromlist(l,j +1)/cols < fromlist(l,j)/cols)
	    swap(l, j, j+1);
	}
    }
}

void bubble_sort_lines(List *l, int cols)
{
  int i = 0, n = size(l);
  for(i = n-1; i>0; i--)
    {
      for(int j = 0; j<i; j++)
	{
	  if(fromlist(l,j +1)%cols < fromlist(l,j)%cols)
	    swap(l, j, j+1);
	}
    }
}

void assemble(List *pos, int cols)
{
  //moyenne ou mediane des espaces de hauteur
  //=> rassembler en ligne liste chainée separée de balises
  //puis sur ces lignes faire la moyenne des espaces
  //=> ordonner les abcisses en ordre croissant
  //=> inserer des espaces.
  //tranformer cette liste en string avec un parcours.

  int i = 0, n = size(pos);
  double moy_y = 0;
  
  List *work = initialisation();
  copy(pos, work);
  bubble_sort_cols(work, cols);
  
  for(i = 0; i< n -1 ; i++)
    {
      moy_y += fromlist(pos,i) - fromlist(pos, i+1);
    }
  moy_y = moy_y/i;
  
  for(i = 0; i<n-1; i++)
    {
      if(fromlist(work,i+1) - fromlist(work,i) > moy_y)
	{
	  insertion_n(work, -3, i+1);
	  n++;
	  i++;
	}
    }
  print_list(work,1);

  //interlignes ok
  
  for(i = 0; i < n; i++)
    {
      //List *l = substring(l,0,-3)
    }
  
}
