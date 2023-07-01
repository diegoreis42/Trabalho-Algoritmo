#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/btree.h"
/* Esse programa compara o tempo de pesquisa usando busca linear
 * e utilizando os indices da b-tree
 * */
int main ()
{
  int indexes[10000];

  clock_t begin = clock();
    // chama a funçao aqui
  clock_t end = clock();

  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;


  return 0;
}

