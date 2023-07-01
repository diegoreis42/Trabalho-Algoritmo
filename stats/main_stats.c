#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/btree.h"
/* Esse programa compara o tempo de pesquisa usando busca linear
 * e utilizando os indices da b-tree
 * */
int main ()
{
  FILE *f = fopen(FILE_NAME, "r");

  clock_t begin = clock();
    // chama a funçao aqui
    printLineLinear(f, 6059);
  clock_t end = clock();

  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Tempo da busca Linear: %f\n", time_spent);


  return 0;
}

