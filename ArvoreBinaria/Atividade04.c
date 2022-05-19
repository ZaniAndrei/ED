#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct NoFila* PtrNoFila;
typedef struct NoArvore* PtrNoArvore;

typedef struct NoFila{
  int pagina;
  PtrNoFila proximo;
}NoFila;

typedef struct{
  PtrNoFila inicio;
  PtrNoFila fim;
  int qtde;
}Fila;

typedef struct NoArvore{
  char chaves[100];
  PtrNoArvore direita;
  PtrNoArvore esquerda;
  Fila fila;
}NoArvore;

void iniciaFila(Fila *fila){
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->qtde = 0;
}


void iniciaArvoreBinaria(PtrNoArvore *no){
  (*no) = NULL;
}

bool estaVaziaArvoreBinaria(PtrNoArvore *no){
  return ((*no) == NULL);
}

bool estaVaziaFila(Fila *fila){
  return(fila->qtde == 0);
}

bool insereArvoreBinaria(PtrNoArvore *no, char *chaves){
  if ((*no) == NULL) {
    (*no) = malloc(sizeof(NoArvore));
    (*no)->direita = NULL;
    (*no)->esquerda = NULL;
    strcpy((*no)->chaves, chaves);
    iniciaFila(&(*no)->fila);
    return true;
  }
  if (strcmp((*no)->chaves, chaves) == 0) {
    return false;
  }
  if (strcmp((*no)->chaves, chaves) < 0) {
    return(insereArvoreBinaria(&(*no)->direita, chaves));
  }else{
    return(insereArvoreBinaria(&(*no)->esquerda, chaves));
  }
}

void inserirFila(Fila *fila, int pagina){
  PtrNoFila novo = malloc(sizeof(NoFila));
  novo->pagina = pagina;
  novo->proximo = NULL;
  if (estaVaziaFila(fila)) {
    fila->inicio = novo;
  }
  else{
    fila->fim->proximo = novo;
  }
  fila->fim = novo;
  fila->qtde++;
}

void imprimeFila(Fila *fila){
  PtrNoFila aux;
  for (aux = fila->inicio; aux != NULL; aux = aux->proximo) {
    printf(",%d", aux->pagina);
  }
  printf("\n");
}

void emOrdemArvoreBinaria(PtrNoArvore *no){
  if ((*no) == NULL) return;
  emOrdemArvoreBinaria(&(*no)->esquerda);
  printf("%s",(*no)->chaves);
  imprimeFila(&(*no)->fila);
  emOrdemArvoreBinaria(&(*no)->direita);
}


bool procuraArvoreBinaria(PtrNoArvore *no, char *palavrasTexto, int pagina){
   if ((*no) == NULL) return false;
   if (strcmp((*no)->chaves, palavrasTexto)== 0){
     inserirFila(&(*no)->fila, pagina);
     return true;
   }
   //recursao
   //valor > no.x -> subarvore direita
   if (strcmp((*no)->chaves, palavrasTexto) < 0) {
    return(procuraArvoreBinaria(&(*no)->direita, palavrasTexto, pagina));
  }else{
    return(procuraArvoreBinaria(&(*no)->esquerda, palavrasTexto, pagina));
  }
}


int main(int argc, char const *argv[]) {
  PtrNoArvore a;
  Fila f;
  char palavra[100];
  bool termosFile = true;
  int pagina;
  char* token;

  FILE* arq1 = fopen("entrada1.txt", "r");
  if (arq1 == NULL) {
    printf("Erro no arquivo de entrada\n");
    return 1;
  }
  FILE* arq2 = fopen("saida.txt", "w");
  if (arq2 == NULL) {
    printf("Erro no arquivo de saida\n");
    return 1;
  }
  iniciaArvoreBinaria(&a);

  while (!feof(arq1)) {
    //se for a primeira linha ele ira pegar os termos a serem inseridos na arvore
    if (termosFile) {
      fgets(palavra, 100, arq1);
      //separa os termos em tokens
      token = strtok(palavra, "<:,>\n");
      //ao colocar essa funçao uma vez aqui evitamos que "termos" seja inserido
      token = strtok(NULL, "<:,>\n");
      while (token != NULL) {
        //printf("Termos: %s\n", token);
        insereArvoreBinaria(&a, token);
        token = strtok(NULL, "<:,>\n");
      }
      //nao permite a entrada novamente
      termosFile = false;
    }
    fgets(palavra, 100, arq1);
    if (palavra[0] == '<') {
      //separa a pagina em um token
      token = strtok(palavra, ":>\n");
      //evita que "page" seja colocado
      token = strtok(NULL, ":>\n");
      while (token != NULL) {
        //printf("Pagina: %s\n",token);
        pagina = atoi(token);
        token = strtok(NULL, ":>\n");
      }
    }
    //separa as palavras em tokens
    token = strtok(palavra, " ,.\n");
    while (token != NULL) {
      if (procuraArvoreBinaria(&a, token, pagina)) {

      }
      token = strtok(NULL, " ,.\n");
    }
  }

  //insereArvoreBinaria(&a, "Amanda");
  emOrdemArvoreBinaria(&a);

  fclose(arq1);
  fclose(arq2);
  return 0;
}
