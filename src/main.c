#include <stdlib.h>
#include <stdio.h>
#include "btree.h"



int main ()
{
  int choice;
  
do {
  printf("1. Criar indice\n");
  printf("2. Procurar Elemento\n");
  printf("3. Remover registro\n");
  printf("4. Sair\n");
  scanf("%d", &choice);

  switch (choice) {
    case 1:
      //chama funçao criar indice
    case 2:
      //chama funçao Procurar elemento
    case 3:
      // chama funçao remover regstro
    case 4:
      printf("Ate mais!\n");
    default:
      printf("Tem essa opçao nao\n");
       
  }
}while (choice != 0);

  return 0;
}