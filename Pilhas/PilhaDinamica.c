#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct NoPilha* PtrNoPilha;
typedef struct NoPilha{
  int x;
  PtrNoPilha proximo;
}NoPilha;

typedef struct{
  PtrNoPilha topo;
  int qtde;
}PilhaDinamica;

void iniciarPilhaDinamica(PilhaDinamica *pilha){
  pilha->qtde = 0;
  pilha->topo = NULL;

}

bool estaVaziaPilhaDinamica(PilhaDinamica *pilha){
  return(pilha->topo == NULL);
}

int tamanhoPilhaDinamica(PilhaDinamica *pilha){
  return(pilha->qtde);
}

void imprimirPilhaDinamica(PilhaDinamica *pilha){
  printf("Pilha = [");
   //cria aux
   //aux recebe topo
   PtrNoPilha aux = pilha->topo;
   //enquanto aux != NULL
   // printa aux->x
   while (aux != NULL) {
     printf("%d ",aux->x);
     aux = aux->proximo;
   }

  printf("]\n");
}
void empilharPilhaDinamica(PilhaDinamica *pilha, int valor){
  //criar novo nó
  PtrNoPilha novo = malloc(sizeof(NoPilha));
  //copiar valor do novo nó
  novo->x = valor;
  //atualizar ptrs
  //proximo novo = topo
  novo->proximo = pilha->topo;
  //topo = novo
  pilha->topo = novo;
  //qtde++
  pilha -> qtde++;
}

void desempilhaPilhaDinamica(PilhaDinamica *pilha){
  if(!estaVaziaPilhaDinamica(pilha)){
    //criar aux
    PtrNoPilha aux;
    //aux salva o no a ser removido
    aux = pilha->topo;
    //atualizar o topo
    pilha->topo = pilha->topo->proximo;
    //liberar memoria
    free(aux);
    pilha->qtde--;
  }
  //qtde --
}

int main(){
  PilhaDinamica p;
  iniciarPilhaDinamica(&p);

  imprimirPilhaDinamica(&p);

  empilharPilhaDinamica(&p, 7);
  imprimirPilhaDinamica(&p);//[7]
  int tam = tamanhoPilhaDinamica(&p);
  printf("Tamanho da Pilha: %d\n", tam);

  empilharPilhaDinamica(&p, 8);
  imprimirPilhaDinamica(&p);//[7,8]
  tam = tamanhoPilhaDinamica(&p);
  printf("Tamanho da Pilha: %d\n", tam);

  empilharPilhaDinamica(&p, 3);
  imprimirPilhaDinamica(&p);//[7,8,3]
  tam = tamanhoPilhaDinamica(&p);
  printf("Tamanho da Pilha: %d\n", tam);

  for (size_t i = 0; i < tam; i++) {
    desempilhaPilhaDinamica(&p);
  }
}
