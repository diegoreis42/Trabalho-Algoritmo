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
  double mean = 0.0, time_spent, max = 0, min = 0; 
  int randN;
  FILE *f = fopen(FILE_NAME, "r");

// calcula a media, valor max e min para 30 buscas aleatorias
  for(int i = 0; i < SEARCH_NUM; i++) {
    randN = rand() % NUM_ELEM + 1;

    clock_t begin = clock();
      printLineLinear(f, randN);
    clock_t end = clock();

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    mean += time_spent;

    if (time_spent > max)
      max = time_spent;

    if (time_spent < min)
      min = time_spent;
  }

  printf("Tempo medio da busca Linear: %f\n", (double) mean / SEARCH_NUM);
  printf("Menor tempo da busca Linear: %f\n", min);
  printf("Maior tempo da busca Linear: %f\n", max);


  fclose(f);
  return 0;
}

