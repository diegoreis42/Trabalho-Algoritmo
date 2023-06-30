#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


int * leArquivo(){
  FILE *f = fopen("table.txt", "r");
  char line[100];
  int indexes[10000];
  int j = 0;

  while (fgets(line, sizeof(line), f) != NULL) {
      sscanf(line, "%d", &indexes[j]);
    j++;
  }
  fclose(f);

  return indexes;
}


