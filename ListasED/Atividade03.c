#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct NoLista* PtrNoLista;

typedef struct{
  char nome[100];
  char sexo[2];
  int idade;
  int codigo;
  float peso;
  float altura;
  char telefone[16];
}Cadastro;

typedef struct NoLista{
  Cadastro cadastro;
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





void imprimirListaCrescente(ListaDupla *lista, Cadastro cadastro){
  printf("\n");
  PtrNoLista percorre;
  for (percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo) {

    printf("{%d, %s, %s, ", percorre->cadastro.codigo, percorre->cadastro.nome, percorre->cadastro.sexo);
    printf("%d,%.2f,%.2f,%s\n", percorre->cadastro.idade, percorre->cadastro.peso, percorre->cadastro.altura, percorre->cadastro.telefone);
    if (percorre == lista->inicio->anterior) {
      break;
    }
  }
  printf("\n");
}

void imprimirListaDecrescente(ListaDupla *lista, Cadastro cadastro){
  printf("\n");
  PtrNoLista percorre;
  for (percorre = lista->inicio->anterior; percorre != NULL; percorre = percorre->anterior) {

    printf("{%d, %s, %s, ", percorre->cadastro.codigo, percorre->cadastro.nome, percorre->cadastro.sexo);
    printf("%d,%.2f,%.2f,%s\n", percorre->cadastro.idade, percorre->cadastro.peso, percorre->cadastro.altura, percorre->cadastro.telefone);
    if (percorre == lista->inicio) {
      break;
    }
  }
  printf("\n");
}

void inserirListaDupla(ListaDupla *lista, Cadastro cadastro){
  PtrNoLista novo;
  novo = (PtrNoLista)malloc(sizeof(NoLista));
  novo->cadastro.codigo = cadastro.codigo;
  strcpy(novo->cadastro.nome,cadastro.nome);
  strcpy(novo->cadastro.sexo,cadastro.sexo);
  novo->cadastro.idade = cadastro.idade;
  novo->cadastro.peso = cadastro.peso;
  novo->cadastro.altura = cadastro.altura;
  strcpy(novo->cadastro.telefone, cadastro.telefone);






  if (estaVaziaLista(lista)) {
    //inserir o primeiro elemento: Ponteiro aponta para ela mesma ptr.inicio.prox = ptr
    novo->proximo = novo;
    novo->anterior = novo;
    lista->inicio = novo;
  }else if (novo->cadastro.codigo < lista->inicio->cadastro.codigo) {
    novo->proximo = lista->inicio;
    novo->anterior = lista->inicio->anterior;
    lista->inicio->anterior->proximo = novo;
    lista->inicio->anterior = novo;
    lista->inicio = novo;
  }else if ((novo->cadastro.codigo > lista->inicio->cadastro.codigo) && (novo->cadastro.codigo < lista->inicio->anterior->cadastro.codigo)) {
    PtrNoLista percorre;
    percorre = lista->inicio;
    while ((percorre->proximo != lista->inicio->anterior) && (novo->cadastro.codigo > percorre->proximo->cadastro.codigo)) {
      percorre = percorre->proximo;
    }
    novo->proximo = percorre->proximo;
    novo->anterior = percorre;
    percorre->proximo->anterior = novo;
    percorre->proximo = novo;
    }
  else if (novo->cadastro.codigo > lista->inicio->anterior->cadastro.codigo) {
    novo->proximo = lista->inicio;
    novo->anterior = lista->inicio->anterior;
    lista->inicio->anterior->proximo = novo;
    lista->inicio->anterior = novo;
  }
}

void buscaLista(ListaDupla *lista, int busca){
  PtrNoLista percorre;

  while (percorre != lista->inicio->anterior && busca ) {
    /* code */
  }
}


int main(int argc, char const *argv[]) {
 ListaDupla l;
 Cadastro cadastro;
 char* ptr;
 char* resultado;
 bool cond = true;
 char palavra[100];
 int operacao;
 iniciaLista(&l);
 int buscaContador = 0;
 int busca;
 int contador;
 FILE* arq1 = fopen("entrada.txt", "r");
 //ptr = strtok(palavra, "{,}\n");
 while(!feof(arq1)){
   contador = 0;
   fgets(palavra, 100 ,arq1);
   ptr = strtok(palavra, "{,}\n");
   if (palavra[0] == '{') {
     while (ptr != NULL) {
       if (contador == 0) {
         cadastro.codigo = atoi(ptr);
         printf("Codigo: %d\n", cadastro.codigo);
       }else if (contador == 1) {
         strcpy(cadastro.nome, ptr);
         printf("NOme: %s\n",cadastro.nome);
       }else if (contador == 2) {
         strcpy(cadastro.sexo, ptr);
         printf("Sexo: %s\n",cadastro.sexo);
       }
       else if (contador == 3) {
         //converte a string para inteiro
         cadastro.idade = atoi(ptr);
         printf("Idade: %d\n",cadastro.idade);
       }
       else if (contador == 4) {
         //converte a string para float
         cadastro.peso = strtod(ptr, NULL);
         printf("Peso: %.2f\n",cadastro.peso);
       }
       else if (contador == 5) {
         //converte a string para float
         cadastro.altura = strtod(ptr, NULL);
         printf("Altura: %.2f\n",cadastro.altura);
       }
       else if (contador == 6) {
         strcpy(cadastro.telefone, ptr);
         printf("Telefone: %s\n",cadastro.telefone);
       }

       ptr = strtok(NULL, "{,}\n");
       contador++;

     }
     if (contador != 7) {
       printf("Dados insuficientes\n");
       exit(1);
     }else{

     inserirListaDupla(&l, cadastro);
     printf("\n");
   }
  }else{
    if (buscaContador == 0) {
      operacao = atoi(palavra);
      printf("Operacao: %d\n", operacao);
      buscaContador++;
    }else if(buscaContador == 1){
      busca = atoi(palavra);
      printf("Busca: %d\n", busca);
      buscaContador++;
    }
  }
 }
 switch (operacao) {
   case 1:
    printf("Operacao 1 escolhida, iniciando consulta...\n");
    buscaLista(&l, busca);
    break;
   case 2:
    printf("Operacao 2 escolhida, mostrando em ordem crescente:\n");
    imprimirListaCrescente(&l, cadastro);
    break;
   case 3:
    printf("Operacao 3 escolhida, imprimindo em ordem decrescente:\n");
    imprimirListaDecrescente(&l, cadastro);
    break;
   default:
    printf("Operacao invalida\n");
    exit(1);
    break;
 }

 return 0;
}
