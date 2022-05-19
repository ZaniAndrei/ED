#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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

bool percorreFila(Fila *fila, int busca){
  PtrNoFila percorre;
  for (percorre = fila->inicio; percorre != NULL; percorre = percorre->proximo) {
    if (percorre->pagina == busca) {
      return true;
    }
  }
  return false;
}


void inserirFila(Fila *fila, int pagina){
  if (!percorreFila(fila, pagina)) {
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
}
void tamanhoFila(Fila *fila){

}


void imprimeFila(Fila *fila, FILE* arq){
  PtrNoFila aux;
  for (aux = fila->inicio; aux != NULL; aux = aux->proximo) {
    fprintf(arq, ",%d", aux->pagina);
  }
}

void emOrdemArvoreBinaria(PtrNoArvore *no, FILE* arq){
  if ((*no) == NULL) return;
  emOrdemArvoreBinaria(&(*no)->esquerda, arq);
  fprintf(arq,"%s",(*no)->chaves);
  imprimeFila(&(*no)->fila, arq);
  fprintf(arq, "\n");
  emOrdemArvoreBinaria(&(*no)->direita, arq);
}


bool procuraArvoreBinaria(PtrNoArvore *no, char *palavrasTexto, int pagina){
   if ((*no) == NULL) return false;
   if (strcmp((*no)->chaves, palavrasTexto)== 0){
     inserirFila(&(*no)->fila, pagina);
     return true;
   }
   if (strcmp((*no)->chaves, palavrasTexto) < 0) {
    return(procuraArvoreBinaria(&(*no)->direita, palavrasTexto, pagina));
  }else{
    return(procuraArvoreBinaria(&(*no)->esquerda, palavrasTexto, pagina));
  }
}

void converteMaiusculo(char* palavra){
  int tamanho = strlen(palavra);
  for (int i = 0; i < tamanho; i++) {
  palavra[i] = tolower(palavra[i]);
  }
  palavra[tamanho] = '\0';
}

void destroiArvore(PtrNoArvore *no){
  if((*no) != NULL) {
    destroiArvore(&(*no)->esquerda);
    destroiArvore(&(*no)->direita);
    free(*no);
    *no = NULL;
  }
}


int main(int argc, char const *argv[]) {
  PtrNoArvore a;
  Fila f;
  char palavra[700];
  bool termosFile = true;
  int pagina;
  char* token;

  if (argc != 3) {
    printf("Utilize 3 argumentos somente\n");
    return 1;
  }
  
  FILE* arq1 = fopen(argv[1], "r");
  if (arq1 == NULL) {
    printf("Erro no arquivo de entrada\n");
    return 1;
  }
  FILE* arq2 = fopen(argv[2], "w");
  if (arq2 == NULL) {
    printf("Erro no arquivo de saida\n");
    return 1;
  }
  iniciaArvoreBinaria(&a);

  while (!feof(arq1)) {
    //se for a primeira linha ele ira pegar os termos a serem inseridos na arvore
    if (termosFile) {
      //700 pra pegar a linha inteira dos arquivos(algumas deram 600 e pouco)
      fgets(palavra, 700, arq1);
      //separa os termos em tokens
      token = strtok(palavra, "<:,>\n");
      //ao colocar essa funçao uma vez aqui evitamos que "termos" seja inserido
      token = strtok(NULL, "<:,>\n");
      while (token != NULL) {
        /*converte para minusculo para achar corretamente as palavras no texto
        (será feito com as palavras mais adiante também)*/
        converteMaiusculo(token);
        //printf("Termos: %s\n", token);
        insereArvoreBinaria(&a, token);
        token = strtok(NULL, "<:,>\n");
      }
      //nao permite a entrada novamente
      termosFile = false;
    }
    fgets(palavra, 700, arq1);
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
    token = strtok(palavra, " ,.\n();{}[]");

    while (token != NULL) {
      converteMaiusculo(token);
      //printf("Texto: %s\n",token);
      if (procuraArvoreBinaria(&a, token, pagina)) {

      }
      token = strtok(NULL, " ,.\n();{}[]");
    }
  }
  emOrdemArvoreBinaria(&a, arq2);

  destroiArvore(&a);
  fclose(arq1);
  fclose(arq2);
  return 0;
}
