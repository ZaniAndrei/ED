#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 3

typedef struct{
  int vetorPilha[TAMANHO];
  int topoPilha;
}pilhaDecimal;

//funão para inicializar a piha e inserir os dados logo após
void inicializaPilha(pilhaDecimal *decimal){
  decimal->topoPilha = -1;
}


//funções condicionais que serão utilizadas para auxiliar no preenchimento e remoção da pilha
bool estaVaziaPilha(pilhaDecimal *decimal){
  return(decimal->topoPilha == -1);
}
bool estaCheiaPilha(pilhaDecimal *decimal){
  return(decimal->topoPilha == TAMANHO - 1);
}

//f
//void empilhaNumeros(pilhaDecimal *decimal, )

int converteDecimal(pilhaDecimal *decimal, int i, FILE *arq2){
  int aux = 0;
  while (decimal->numerosArquivo[i] / 2 > 0) {
      decimal->vetorPilha[aux] = decimal->numerosArquivo[i] % 2;
      aux++;
      decimal->numerosArquivo[i] = decimal->numerosArquivo[i] / 2;
  }
  for (size_t j = aux; aux > 0; aux--) {
    fprintf(arq2, "%d", decimal->vetorPilha[aux]);
  }
}

void imprimeNumeros(pilhaDecimal *decimal){
  for (size_t i = 0; i < TAMANHO; i++) {
    printf("%d\n");
  }
}

int main(int argc, char *argv[]) {
  pilhaDecimal d;

  inicializaPilha(&d);
  FILE *arq1 = fopen("decimal.txt","r");
  if (arq1 == NULL) {
    printf("ERRO NO ARQUIVO!\n");
    exit(1);
  }
  while (!feof(arq1)) {
    d.topoPilha++;
    fscanf(arq1, "%d", &d.vetorPilha[d.topoPilha]);
    printf("%d\n", d.vetorPilha[d.topoPilha]);
  }//while

  FILE *arq2 = fopen("binario.txt","w");
  if (arq2 = NULL) {
    printf("ERRO NO ARQUIVO!\n");
    exit(1);
  }


  /*for (size_t i = 0; i < TAMANHO; i++) {
    converteDecimal(&d, i, arq2);
    fprintf(arq2, "\n");
  }*/

  //imprimeNumeros(&d);
  //empilhaNumeros(&d, 4);
  printf("\n");

  fclose(arq1);
  fclose(arq2);
  return 0;
}
