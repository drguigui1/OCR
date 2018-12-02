# ifndef ANALYSE_H
# define ANALYSE_H
# include "List.h"

List *center(List *l, int cols);

void test();

List *collect_l(Tree *t);
List *collect_pos(Tree *t);


double min_pos(List *l, int cols);
double max_pos(List *l, int cols);

Matrix array_of_contrast(List *l, int rows, int cols);

Matrix coor_to_matrix(List *l, int size);
List *matrix_to_list(Matrix array);
Matrix list_to_matrix(List *l);
int medium(List *l);
Matrix resize(Matrix array,int rows, int columns);

Matrix analyse(Tree *t, Matrix array);



#endif
