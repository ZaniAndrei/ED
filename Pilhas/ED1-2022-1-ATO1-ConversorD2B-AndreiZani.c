#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 50


typedef struct{
  int vetorPilha[TAMANHO];
  int topoPilha;
}pilhaDecimal;

//função para inicializar a piha e inserir os dados logo após
void inicializaPilha(pilhaDecimal *decimal){
  decimal->topoPilha = -1;
}

//funções condicionais que serão utilizadas para controlar quando algo poderá ser retirado ou colocado na pilha
bool estaVaziaPilha(pilhaDecimal *decimal){
  return(decimal->topoPilha == -1);
}
bool estaCheiaPilha(pilhaDecimal *decimal){
  return(decimal->topoPilha == TAMANHO - 1);
}

//essa função vai percorrer o arquivo até o fim, incrementando o topo a cada passagem e armazenando os dados
void empilhaPilhaEstatica(pilhaDecimal *decimal, FILE* arq){
  if (estaCheiaPilha(decimal)) {
    printf("Pilha esta cheia!\n");
  }else{
    while (!feof(arq)) {
      decimal->topoPilha++;
      fscanf(arq, "%d", &decimal->vetorPilha[decimal->topoPilha]);
    }
  }
}


//essa função vai descrescer o topo para indicar a ordem do elemento da pilha que será armazenado
void desempilhaPilhaEstatica(pilhaDecimal *decimal){
  int aux;
  if (estaVaziaPilha(decimal)) {
    printf("Pilha esta vazia! Nao e possivel desempilhar\n");
  }else{
    decimal->topoPilha--;
    }
}

/*essa função vai converter os elementos da pilha em binario e armazenar no
arquivo de saída
*/
void converteDecimal(pilhaDecimal *decimal, FILE* arq){
  //256 vai ser o numero maximo de uns e zeros armazenados
  int vetor[256];
  int x = decimal->vetorPilha[decimal->topoPilha - 1];
  int aux = 0;
  do{
    vetor[aux] = x % 2;
    aux++;
    x /= 2;
  }while(x > 0);
  desempilhaPilhaEstatica(decimal);
  //for para ordenar o binario no arquivo corretamente
  for (int j = aux - 1; j >= 0; j--) {
    fprintf(arq, "%d", vetor[j]);
  }
  }


int main(int argc, char const *argv[]) {
  //error handling sobre os argumentos utilizados na função main
  if (argc != 3 && argc > 3) {
    printf("Muitos argumentos utilizados(utilize 3)\n");
    exit(1);
  }
  if (argc != 3 && argc < 3) {
    printf("Poucos argumentos utilizados(utilize 3)\n");
    exit(1);
  }
  pilhaDecimal d;
  inicializaPilha(&d);
  FILE *arq1 = fopen(argv[1], "r");
  //error handling arquivo 1
  if (arq1 == NULL) {
    printf("ERRO NO ARQUIVO DE ENTRADA\n");
    exit(1);
  }

  empilhaPilhaEstatica(&d, arq1);
  fclose(arq1);

  FILE *arq2 = fopen(argv[2], "w");
  //error handling arquivo 2
  if (arq2 == NULL) {
    printf("ERRO NO ARQUIVO DE SAIDA\n");
    exit(1);
  }
  /*loop vai percorrer os elementos da pilha e transformando-os em decimal,
   quando um numero for convertido, ele pega o proximo elemento da pilha para converter
  */
  for (size_t i = d.topoPilha; i > 0 ; i--) {
    converteDecimal(&d, arq2);
    fprintf(arq2,"\n");
  }
  fclose(arq2);
  return 0;
}
