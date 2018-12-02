#include <stdio.h>
#include <stdlib.h>
#include "Binarisation.h"
#include "Analyse.h"
#include "Restore.h"

int main(int argc, char** argv)
{
  
  if(argc == 2 && argv[1][0] == '1')
    {
      printf("entered");
      Matrix array = init_matrix_zero(100,100);
      Tree *t = binarisation(array);

      printf("resulted tree:\n");
      print_tree(t -> root);
      printf("\n");
      print_matrix(analyse(t, array));
    }
  
  Matrix array = init_matrix_zero(10,10);
  *(array.pt + 22) = 1;
  *(array.pt + 23) = 1;
  *(array.pt + 24) = 1;
  *(array.pt + 32) = 1;
  *(array.pt + 34) = 1;
  *(array.pt + 42) = 1;
  *(array.pt + 43) = 1;
  *(array.pt + 44) = 1;
  *(array.pt + 52) = 1;
  *(array.pt + 54) = 1;
  
  *(array.pt + 68) = 2;
  *(array.pt + 67) = 2;
  *(array.pt + 66) = 2;
  *(array.pt + 77) = 2;
  *(array.pt + 87) = 2;
  
  List *l1 = initialisation();
  insertion(l1,1);
  insertion(l1,2);
  insertion(l1,3);
  insertion(l1,7);
  insertion(l1,8);
  insertion(l1,9);

  Tree *t = binarisation(array);
  
  printf("\n\nArray: \n");
  
  printf("      1.  2.  2.  3.  4.  5.  6.  7.  8.  9.\n\n");
  printf(" .0   0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 \n");
  printf(" .1   0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 \n");
  printf(" .2   0 | 0 |-1-|-1-|-1-| 0 | 0 | 0 | 0 | 0 \n");
  printf(" .3   0 | 0 |-1-| 0 |-1-| 0 | 0 | 0 | 0 | 0 \n");
  printf(" .4   0 | 0 |-1-|-1-|-1-| 0 | 0 | 0 | 0 | 0 \n");
  printf(" .5   0 | 0 |-1-| 0 |-1-| 0 | 0 | 0 | 0 | 0 \n");
  printf(" .6   0 | 0 | 0 | 0 | 0 | 0 |-2-|-2-|-2-| 0 \n");
  printf(" .7   0 | 0 | 0 | 0 | 0 | 0 | 0 |-2-| 0 | 0 \n");
  printf(" .8   0 | 0 | 0 | 0 | 0 | 0 | 0 |-2-| 0 | 0 \n");
  printf(" .9   0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 \n");

  printf("\n");
  

  printf("\nresulted tree:\n");
  print_tree(t -> root);
  printf("\n");
  print_matrix(analyse(t, array));

  free(array.pt);
  
  return (0);
}
