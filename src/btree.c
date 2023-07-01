#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// cabeçalho do arquivo table.txt
#define FIRST_LINE 31
// tamanho de cada linha
#define SIZE_DATA_LINE 41

//nome do arquivo
#define FILE_NAME "../data/table.txt"

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

/* funçao para printar o conteudo de uma linha
 especifica do arquivo table.txt

 Entrada
----------------------
f    ->  ponteiro para o arquivo
line ->  linha do arquivo
*/
void printLineBtree(FILE *f, int line){
  char buffer[50];
  
  fseek(f, FIRST_LINE + (SIZE_DATA_LINE * line), SEEK_SET);
  fgets(buffer, sizeof(buffer), f);
  printf("%s\n", buffer);
  rewind(f);
}

/* funçao para printar o conteudo de uma linha
 * do arquivo table.txt, procurando linearmente!
 *
 *  Entrada  
 * -----------------
 * f  -> ponteiro para o arquivo
 * id -> identificador da linha
 *
 * Saida
 * -----------------
 * 0 -> Nao encontrou o id
 * 1 -> Encontrou o id
 */
int printLineLinear(FILE *f, int id){
  char buffer[100];
  int h = 0;

  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    sscanf(buffer, "%d", &h);
    if(h == id) {
      printf("%s\n", buffer);
      rewind(f);
      return 1;
    }
  }

  return 0;
}


