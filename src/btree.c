#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// cabeçalho do arquivo table.txt
#define FIRST_LINE 31
// tamanho de cada linha
#define SIZE_DATA_LINE 41

//nome do arquivo
#define FILE_NAME "table.txt"

typedef struct elem {
  int key;
  int line;
}Elem;

// Funçao para ler ID das linhas e armazenar em um vetor
void leArquivo(int *indexes){
  FILE *f = fopen(FILE_NAME, "r");
  char line[100];
  int j = 0;


  while (fgets(line, sizeof(line), f) != NULL) {
    sscanf(line, "%d", &indexes[j]);
    j++;
  }

  fclose(f);
}

void printLine(FILE *f, int line){
  char buffer[50];
  
  fseek(f, FIRST_LINE + (SIZE_DATA_LINE * line), SEEK_SET);
  fgets(buffer, sizeof(line), f);
  printf("%s\n", buffer);
}


int main() {
    int buffer[10000];
    char line[256];
    FILE *f = fopen(FILE_NAME, "r");
      

    return 0;
}
