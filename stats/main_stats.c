// made by Diego Reis



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/btree.h"

#define SEARCH_NUM 30
#define NUM_ELEM 10000

/* Esse programa compara o tempo de pesquisa usando busca linear
 * e utilizando os indices da b-tree
 * */
int main ()
{
  srand(time(NULL));
  double mean = 0.0, time_spent; 
  int randN;
  FILE *f = fopen(FILE_NAME, "r");


  for(int i = 0; i < SEARCH_NUM; i++) {
    randN = rand() % NUM_ELEM + 1;

    clock_t begin = clock();
      printLineLinear(f, randN);
    clock_t end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    mean += time_spent;
  }

  printf("Tempo medio da busca Linear: %.4f\n", (double) mean / SEARCH_NUM);


  fclose(f);
  return 0;
}

