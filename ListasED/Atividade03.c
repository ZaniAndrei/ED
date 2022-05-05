#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct NoLista* PtrNoLista;

typedef struct NoLista{
  char nome[100];
  char sexo[2];
  int idade;
  int codigo;
  float peso;
  float altura;
  char telefone[16];
  PtrNoLista proximo;
  PtrNoLista anterior;
}NoLista;

typedef struct{
  PtrNoLista inicio;
}ListaDupla;


//primeiro caso: menor que o inicio
//segundo caso: maior que o final
//terceiro caso: maior que o inicio menor que o final
//
//
//
//
//
void iniciaLista(ListaDupla *lista){
  lista->inicio = NULL;
}

bool estaVaziaLista(ListaDupla *lista){
  return(lista->inicio == NULL);
}





void imprimirListaDinamica(ListaDupla *lista){
  printf("Lista = {");
  PtrNoLista percorre;
  for (percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo) {

    printf("%d ", percorre->codigo);
    if (percorre == lista->inicio->anterior) {
      break;
    }
  }
  printf("}\n");
}

void inserirListaDupla(ListaDupla *lista, int elemento){
  PtrNoLista novo;
  novo = (PtrNoLista)malloc(sizeof(NoLista));
  novo->codigo = elemento;

  if (estaVaziaLista(lista)) {
    //inserir o primeiro elemento: Ponteiro aponta para ela mesma ptr.inicio.prox = ptr
    lista->inicio = novo;
    novo->proximo = novo;
    novo->anterior = novo;
  }else if (novo->codigo < lista->inicio->codigo) {
    novo->proximo = lista->inicio;
    novo->anterior = lista->inicio->anterior;
    lista->inicio->anterior->proximo = novo;
    lista->inicio->anterior = novo;
    lista->inicio = novo;
  }else if ((novo->codigo > lista->inicio->codigo) && (novo->codigo < lista->inicio->anterior->codigo)) {
    PtrNoLista percorre;
    printf("Condicao tipo 3: %d\n",novo->codigo);
    for (percorre = lista->inicio; novo->codigo < percorre->proximo->codigo;percorre->proximo) {
      printf("parou?\n");
      if (novo->codigo < percorre->proximo->codigo) {
        printf("sla\n");
        novo->proximo = percorre->proximo;
        novo->anterior = percorre;
        percorre->proximo->anterior = novo;
        percorre->proximo = novo;
      }
    }
  }
  else if (novo->codigo > lista->inicio->anterior->codigo) {
    novo->proximo = lista->inicio;
    novo->anterior = lista->inicio->anterior;
    lista->inicio->anterior->proximo = novo;
    lista->inicio->anterior = novo;
  }
}




int main(int argc, char const *argv[]) {
  ListaDupla l;
  PtrNoLista elementos;
  char* ptr;
  char* resultado;
  char palavra[100];
  int operacao;
  int contadorCond;
  iniciaLista(&l);

  FILE* arq1 = fopen("entrada.txt", "r");
  ptr = strtok(palavra, "{,}\n");

  while (!feof(arq1)) {
    int contador = 0;
    resultado = fgets(palavra, 100, arq1);
    if (palavra[0] == '{') {
      if (resultado) {
        ptr = strtok(resultado, "{,}\n");
      }
      while (ptr != NULL) {
        if (contador == 0 && operacao == 0) {
          //converte a string para inteiro
          elementos->codigo = atoi(ptr);
          printf("e pra funfar\n");
          printf("Codigo: %d\n",elementos->codigo);
          //inserirListaDupla(&l, elementos->codigo);
        }
        if(contador == 1){
          strcpy(elementos->nome, ptr);
          printf("Nome: %s\n",elementos->nome);
        }
        if (contador == 2) {
          strcpy(elementos->sexo, ptr);
          printf("Sexo: %s\n",elementos->sexo);
        }
        if(contador == 3){
          //converte a string para inteiro
          elementos->idade = atoi(ptr);
          inserirListaDupla(&l, elementos->idade);
          imprimirListaDinamica(&l);
          printf("Idade: %d\n",elementos->idade);
        }
        if (contador == 4) {
          //converte a string para float
          elementos->peso = strtod(ptr, NULL);
          printf("Peso: %.2f\n",elementos->peso);
        }
        if (contador == 5) {
          //converte a string para float
          elementos->altura = strtod(ptr, NULL);
          printf("Altura: %.2f\n",elementos->altura);
        }
        if (contador == 6) {
          strcpy(elementos->telefone, ptr);
          printf("Telefone: %s\n",elementos->telefone);
        }else if(contador > 6){
          printf("fodase\n");
        }
        ptr = strtok(NULL, "{,}\n");
        printf("Contador: %d\n", contador);
        contador++;
    }
  printf("\n");
  }else{
    operacao = atoi(palavra);
    printf("Operador:%d \n", operacao);
  }
}
  printf("Elemento: %d\n",elementos->idade);
  return 0;
}
