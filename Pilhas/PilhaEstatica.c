#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 10

//definição do tipo abstrato de Pilha
typedef struct{
  int vetor[TAMANHO];
  int topo;
}PilhaEstatica;
//pilha estática
//int vetor
//topo (int)

//inicialização da pilha(inicia/cria)
void iniciaPilhaEstatica(PilhaEstatica *pilha){
    //atribuir -1 para topo
    pilha->topo = -1;
}

bool estaVaziaPilhaEstatica(PilhaEstatica *pilha){
  return(pilha->topo == -1);
}

bool estaCheiaPilhaEstatica(PilhaEstatica *pilha){
  return(pilha->topo == (TAMANHO - 1));
}

int tamanhoPilhaEstatica(PilhaEstatica *pilha){
  return(pilha->topo + 1);
}


void imprimePilhaEstatica(PilhaEstatica *pilha){
  printf("Pilha = [");
  for (size_t i = 0; i < TAMANHO; i++) {
    printf("%d ",pilha->vetor[i]);
  }
  printf("]\n");
}
//inserção -> empilhar -> push
void empilharPilhaEstatica(PilhaEstatica *pilha, int x){
  if (estaCheiaPilhaEstatica(pilha)) {
    printf("PILHA CHEIA\n");
  }else{
    pilha->topo++;
    pilha->vetor[pilha->topo] = x;
  }
}
void desempilharPilhaEstatica(PilhaEstatica *pilha){
  int aux = -999;
  if (estaVaziaPilhaEstatica(pilha)) {
    printf("NAO SE PODE RETIRAR UMA PILHA VAZIA\n");
  }else{
    aux = pilha->vetor[pilha->topo];
    pilha->topo--;
  }
  printf("Elemento removido: %d\n",aux);
}
//se tiver vazia nao desempilha(faz nada)
//senao:
//salvar o valor contido na posicao vetor[topo] em alguma variavel
//decrementa o topo
//retorna o valor pra main


int main(int argc, char const *argv[]) {
  PilhaEstatica p;
  int tam;
  //starta a pilha(topo = -1)
  iniciaPilhaEstatica(&p);
  //adiciona elementos
  empilharPilhaEstatica(&p, 42);
  empilharPilhaEstatica(&p, 3);
  empilharPilhaEstatica(&p, 69);
  empilharPilhaEstatica(&p, 79);
  empilharPilhaEstatica(&p, 23);
  empilharPilhaEstatica(&p, 43);
  empilharPilhaEstatica(&p, 12);
  empilharPilhaEstatica(&p, 125);
  empilharPilhaEstatica(&p, 21);
  empilharPilhaEstatica(&p, 51);
  
  imprimePilhaEstatica(&p);
  tam = tamanhoPilhaEstatica(&p);
  printf("Tamanho pilha = %d\n",tam);


  desempilharPilhaEstatica(&p);
  imprimePilhaEstatica(&p);

  empilharPilhaEstatica(&p, 12);
  imprimePilhaEstatica(&p);

  return 0;
}
