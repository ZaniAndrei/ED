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
  int tamanho;
}ListaDupla;


//primeiro caso: menor que o inicio
//segundo caso: maior que o final
//terceiro caso: maior que o inicio menor que o final
//
//
//
//
//
int tamanhoListaNoSentinela(ListaDupla *lista){
  return(lista->tamanho);
}


void iniciaLista(ListaDupla *lista){
  //inicializando o no sentinela
  PtrNoLista sentinela = malloc(sizeof(NoLista));
  sentinela->cadastro.codigo = -999;
  sentinela->proximo = sentinela;
  sentinela->anterior = sentinela;
  lista->inicio = sentinela;
  lista->tamanho = 0;
}

bool estaVaziaLista(ListaDupla *lista){
  return(lista->tamanho == 0);
}


void imprimirListaCrescente(ListaDupla *lista, Cadastro cadastro, FILE* arq){
  PtrNoLista percorre;
  for (percorre = lista->inicio->proximo; percorre != lista->inicio; percorre = percorre->proximo) {
    fprintf(arq,"{%d,%s,%s,", percorre->cadastro.codigo, percorre->cadastro.nome, percorre->cadastro.sexo);
    fprintf(arq,"%d,%.2f,%.2f,%s}\n", percorre->cadastro.idade, percorre->cadastro.peso, percorre->cadastro.altura, percorre->cadastro.telefone);
  }
}

void imprimirListaDecrescente(ListaDupla *lista, Cadastro cadastro, FILE* arq){
  PtrNoLista percorre;
  for (percorre = lista->inicio->anterior; percorre != lista->inicio; percorre = percorre->anterior) {
    fprintf(arq,"{%d,%s,%s,", percorre->cadastro.codigo, percorre->cadastro.nome, percorre->cadastro.sexo);
    fprintf(arq,"%d,%.2f,%.2f,%s}\n", percorre->cadastro.idade, percorre->cadastro.peso, percorre->cadastro.altura, percorre->cadastro.telefone);
  }
}

void inserirListaDupla(ListaDupla *lista, Cadastro cadastro){
  PtrNoLista novo;
  novo = (PtrNoLista)malloc(sizeof(NoLista));
  //colocamos todos os dados para serem alocados corretamente com seus devidos ponteiros
  novo->cadastro.codigo = cadastro.codigo;
  strcpy(novo->cadastro.nome,cadastro.nome);
  strcpy(novo->cadastro.sexo,cadastro.sexo);
  novo->cadastro.idade = cadastro.idade;
  novo->cadastro.peso = cadastro.peso;
  novo->cadastro.altura = cadastro.altura;
  strcpy(novo->cadastro.telefone, cadastro.telefone);

  if (estaVaziaLista(lista)) {
    //inserção primeiro elemento
    novo->proximo = lista->inicio;
    lista->inicio->proximo = novo;
    novo->anterior = lista->inicio;
    lista->inicio->anterior = novo;

  }else if (novo->cadastro.codigo <= lista->inicio->proximo->cadastro.codigo) {
    //inserção do elemento que é menor que o inicio da lista
    novo->proximo = lista->inicio->proximo;
    lista->inicio->proximo->anterior = novo;
    lista->inicio->proximo = novo;
    novo->anterior = lista->inicio;

  }else if ((novo->cadastro.codigo >= lista->inicio->proximo->cadastro.codigo) && (novo->cadastro.codigo <= lista->inicio->anterior->cadastro.codigo)) {
    //inserção do elemento que é maior que o inicio e menor que o final
    PtrNoLista percorre;
    for (percorre = lista->inicio->proximo; percorre->proximo->cadastro.codigo <= novo->cadastro.codigo; percorre = percorre->proximo) {
    }
    novo->proximo = percorre->proximo;
    novo->anterior = percorre;
    percorre->proximo->anterior = novo;
    percorre->proximo = novo;
    }
  else if (novo->cadastro.codigo >= lista->inicio->anterior->cadastro.codigo) {
    //inserção do elemento que é maior que o final
    novo->proximo = lista->inicio;
    novo->anterior = lista->inicio->anterior;
    lista->inicio->anterior->proximo = novo;
    lista->inicio->anterior = novo;
  }
  lista->tamanho++;
}

void buscaLista(ListaDupla *lista, int busca, FILE* arq){
  PtrNoLista percorre;
  //loop vai parar no ponteiro anterior ao que queremos encontrar
  for (percorre = lista->inicio->proximo; percorre->proximo->cadastro.codigo < busca; percorre = percorre->proximo) {
    }
    if (percorre->proximo->cadastro.codigo == busca) {
      fprintf(arq,"{%d,%s,%s,", percorre->proximo->cadastro.codigo, percorre->proximo->cadastro.nome, percorre->proximo->cadastro.sexo);
      fprintf(arq,"%d,%.2f,%.2f,%s}\n", percorre->proximo->cadastro.idade, percorre->proximo->cadastro.peso, percorre->proximo->cadastro.altura, percorre->proximo->cadastro.telefone);
    }else{
      fprintf(arq,"Elemento nao encontrado\n");
      }
  }



int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("Argumentos insuficientes\n");
    exit(1);
  }

 ListaDupla l;
 Cadastro cadastro;
 char* ptr;
 char palavra[100];
 int operacao;
 iniciaLista(&l);
 int buscaContador = 0;
 int busca;
 int contador;
 FILE* arq1 = fopen(argv[1], "r");
 if (arq1 == NULL) {
   printf("Erro no arquivo de entrada\n");
   exit(1);
 }
 FILE* arq2 = fopen(argv[2], "w");
 if (arq2 == NULL) {
   printf("Erro no arquivo de saida\n");
   exit(1);
 }
 while(!feof(arq1)){
   contador = 0;
   fgets(palavra, 100 ,arq1);
   /*função vai separar a minha linha do arquivo em tokens, que terão seus
   valores atribuidos de acordo com o que foi pedido*/
   ptr = strtok(palavra, "{,}\n");
   //verifica se é um dado que queremos inserir a partir do primeiro caracter do palavra
   if (palavra[0] == '{') {
     while (ptr != NULL) {
       //contador vai assegurar que colocamos o dado certo no lugar certo
       if (contador == 0) {
         //converte a string pra inteiro
         cadastro.codigo = atoi(ptr);
       }
       else if (contador == 1) {
         strcpy(cadastro.nome, ptr);
       }
       else if (contador == 2) {
         strcpy(cadastro.sexo, ptr);
       }
       else if (contador == 3) {
         //converte a string para inteiro
         cadastro.idade = atoi(ptr);
       }
       else if (contador == 4) {
         //converte a string para float
         cadastro.peso = strtod(ptr, NULL);
       }
       else if (contador == 5) {
         //converte a string para float
         cadastro.altura = strtod(ptr, NULL);
       }
       else if (contador == 6) {
         strcpy(cadastro.telefone, ptr);
       }
       ptr = strtok(NULL, "{,}\n");
       contador++;
     }
     //verifica se foram inseridos todos os dados necessários, caso tenha menos ou mais dados do que o necessário
     if (contador != 7) {
       fprintf(arq2,"Arquivo invalido\n");
       exit(1);
     //se estiver correto fará a inserção
     }else{
       inserirListaDupla(&l, cadastro);
   }
  //se o primeiro caracter do meu arquivo nao for um '{' ele vai entender que será a operação que queremos realizar
  }else{
    /*contador vai assegurar que estamos colocando o numero da operação(1 a 3)
    corretamente e se houver outro número logo após, esse número será o código que
    será buscado na lista*/
    if (buscaContador == 0) {
      operacao = atoi(palavra);
      buscaContador++;
    }else if(buscaContador == 1 && operacao == 3){
      busca = atoi(palavra);
      buscaContador++;
    }
  }
 }
 //switch com as operações que serão feitas
 switch (operacao) {
   case 1:
     imprimirListaCrescente(&l, cadastro, arq2);
     break;
   case 2:
     imprimirListaDecrescente(&l, cadastro, arq2);
     break;
   case 3:
     buscaLista(&l, busca, arq2);
     break;
   default:
     fprintf(arq2,"Arquivo invalido\n");
     exit(1);
     break;
 }

 return 0;
}
