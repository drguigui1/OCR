#include <stdio.h>
#include "binarisation.h"

int main()
{
  
  Matrix array = init_matrix_zero(10,10);
    
  *(array.pt + 2*array.columns + 2) = 5;
  *(array.pt + 1*array.columns + 1) = 1;
  *(array.pt + 2*array.columns + 1) = 1;
  *(array.pt + 3*array.columns + 1) = 1;
  *(array.pt + 1*array.columns + 2) = 1;
  *(array.pt + 3*array.columns + 2) = 1;
  *(array.pt + 1*array.columns + 3) = 1;
  *(array.pt + 2*array.columns + 3) = 1;
  *(array.pt + 3*array.columns + 3) = 1;

  *(array.pt + 5*array.columns + 5) = 2;

  print_Tree(binarisation(array) -> root);
  printf("\n");
  
  return (0);
}
