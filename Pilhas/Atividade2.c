#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*construir um compilador que recebe uma expressão escrita em Notação Pos-fixa
ex: a*b + c -> a b * c +   a*(b+c) -> a b c + *   (a+b)*c -> a b + c *
(a+b)*(cd)->a b + c d + *
EX:
AB*C+ = {LDR B        carrega B
        LDR A        carrega A} desempilha e print no arquivo

        MULT B A     multiplica B e A } switch em desempilha com cada caso(mult nesse)
        STR TEMP1    armazena as variaveis em uma variavel temp1 e empilha temp1
        {LDR C        carrega C
        LDR TEMP1    carrega temp1} desempilha e print no arquivo
        ADD C TEMP1  soma C em temp1} switch em desempilha com cada caso


*/

typedef struct NoPilha* PtrNoPilha;
typedef struct NoPilha{
  char instrucao;
  PtrNoPilha proximo;
}NoPilha;

typedef struct{
  PtrNoPilha topo;
  int qtde;
}PilhaDinamica;
//verifica a validade dos caracteres para ver se a função é terminada ou não
bool caracterValido(char caracter){
  if (caracter >= 65 && caracter <= 122){
    return true;
  }else{
    return false;
  }
}

//verifica a validade das operações especificamente
bool operacaoValida(char caracter){
  if (caracter == 42 || caracter == 43 || caracter == 45 || caracter == 47) {
    return true;
  }else{
    return false;
  }
}


//INICIAR A PILHA
void iniciarPilha(PilhaDinamica *compilador){
  compilador->topo = NULL;
  compilador->qtde = 0;
}
//CONDIÇÃO PARA AUXILIAR NA REMOÇÃO DA PILHA
bool estaVazia(PilhaDinamica *compilador){
  return(compilador->qtde == 0);
}

void empilharElementos(PilhaDinamica *compilador, char caracter, FILE* arq){
  //só ira empilhar os elementos se eles forem validos(funções retornam true)
    PtrNoPilha aux = malloc(sizeof(NoPilha));
    aux->instrucao = caracter;
    aux->proximo = compilador->topo;
    compilador->topo = aux;
    compilador->qtde++;
}

//imprimir para acompanhar o progresso do codigo
void imprimePilha(PilhaDinamica *compilador){
  printf("[ ");

  PtrNoPilha aux = compilador->topo;
  while (aux != NULL) {
    printf("%c ",aux->instrucao);
    aux = aux->proximo;
  }
  printf(" ]\n");
}

void desempilhaInstrucoes(PilhaDinamica *compilador, FILE* arq, char caractere, int* contaTemp){
  //while(!estaVazia(compilador)) {
    //for (size_t i = 0; i < 2; i++) {
      char valor;
      PtrNoPilha aux;
      valor = compilador->topo->instrucao;
      aux = compilador->topo;
      compilador->topo = compilador->topo->proximo;
      free(aux);

      char valor2 = compilador->topo->instrucao;
      aux = compilador->topo;
      compilador->topo = compilador->topo->proximo;
      free(aux);
      if (valor == 'T' && valor2 == 'T') {
        fprintf(arq, "LDR TEMP%d\n", *contaTemp);
        fprintf(arq, "LDR TEMP%d\n", *contaTemp - 1);
      }else if (valor == 'T' && valor2 != 'T' ) {
        fprintf(arq, "LDR TEMP%d\n",*contaTemp);
        fprintf(arq, "LDR %c\n",valor2);
      }else if (valor != 'T' && valor2 == 'T') {
        fprintf(arq, "LDR %c\n",valor);
        fprintf(arq, "LDR TEMP%d\n",*contaTemp);
      }
      else{

        printf("LDR %c\n", valor);
        fprintf(arq, "LDR %c\n", valor);
        printf("LDR %c\n",valor2);
        fprintf(arq, "LDR %c\n", valor2);
    }
    //  }
      switch (caractere) {
        case '*':
        if (valor == 'T' && valor2 == 'T') {
          printf("MULT TEMP%d TEMP%d\n",contaTemp, contaTemp - 1 );
          fprintf(arq, "MULT TEMP%d TEMP%d\n",*contaTemp, *contaTemp - 1);
        }else if (valor == 'T' && valor2 != 'T') {
          fprintf(arq, "MULT TEMP%d %c\n",*contaTemp, valor2);
        }else if (valor != 'T' && valor2 == 'T') {
          fprintf(arq, "MULT %c TEMP%d\n",valor, *contaTemp);
        }
        else{
          printf("MULT %c %c\n",valor, valor2);
          fprintf(arq, "MULT %c %c\n", valor, valor2);
        }
          *contaTemp = *contaTemp + 1;
          empilharElementos(compilador, 'T', arq);
          fprintf(arq, "STR TEMP%d\n",*contaTemp);
          break;
        case '+':
        if (valor == 'T' && valor2 == 'T') {
          printf("ADD TEMP%d TEMP%d\n",contaTemp, contaTemp - 1 );
          fprintf(arq, "ADD TEMP%d TEMP%d\n",*contaTemp, *contaTemp - 1);
        }else if (valor == 'T' && valor2 != 'T') {
          fprintf(arq, "ADD TEMP%d %c\n",*contaTemp, valor2);
        }else if (valor != 'T' && valor2 == 'T') {
          fprintf(arq, "ADD %c TEMP%d\n",valor, *contaTemp);
        }
        else{
          printf("ADD %c %c\n",valor, valor2);
          fprintf(arq, "ADD %c %c\n", valor, valor2);
        }
          *contaTemp = *contaTemp + 1;
          printf("ADD %c %c\n", valor, valor2);
          empilharElementos(compilador, 'T', arq);
          fprintf(arq, "STR TEMP%d\n",*contaTemp);
          break;
        case '/':
        if (valor == 'T' && valor2 == 'T') {
          printf("DIV TEMP%d TEMP%d\n",contaTemp, contaTemp - 1 );
          fprintf(arq, "DIV TEMP%d TEMP%d\n",*contaTemp, *contaTemp - 1);
        }else if (valor == 'T' && valor2 != 'T') {
          fprintf(arq, "DIV TEMP%d %c\n",*contaTemp, valor2);
        }else if (valor != 'T' && valor2 == 'T') {
          fprintf(arq, "DIV %c TEMP%d\n",valor, *contaTemp);
        }
        else{
          printf("DIV %c %c\n",valor, valor2);
          fprintf(arq, "DIV %c %c\n", valor, valor2);
        }
          *contaTemp = *contaTemp + 1;
          printf("DIV %c %c\n", valor, valor2);
          empilharElementos(compilador, 'T',  arq);
          fprintf(arq, "STR TEMP%d\n",*contaTemp);
          break;
        case '-':
        if (valor == 'T' && valor2 == 'T') {
          printf("SUB TEMP%d TEMP%d\n",contaTemp, contaTemp - 1 );
          fprintf(arq, "SUB TEMP%d TEMP%d\n",*contaTemp, *contaTemp - 1);
        }else if (valor == 'T' && valor2 != 'T') {
          fprintf(arq, "SUB TEMP%d %c\n",*contaTemp, valor2);
        }else if (valor != 'T' && valor2 == 'T') {
          fprintf(arq, "SUB %c TEMP%d\n",valor, *contaTemp);
        }
        else{
          printf("SUB %c %c\n",valor, valor2);
          fprintf(arq, "SUB %c %c\n", valor, valor2);
        }
          printf("SUB %c %c\n", valor, valor2);
          *contaTemp = *contaTemp + 1;
          empilharElementos(compilador, 'T',  arq);
          fprintf(arq, "STR TEMP%d\n",*contaTemp);
          break;
        default:
          break;
    }
  //}
}

int main(int argc, char const *argv[]) {
  PilhaDinamica c;
  char caractere;
  iniciarPilha(&c);
  int contaTemp = 0;


  FILE *arq1 = fopen("entrada.txt", "r");
  if (arq1 == NULL) {
    printf("ERRO NO ARQUIVO DE LEITURA\n");
    exit(1);
  }
  FILE *arq2 = fopen("saida.txt", "w");
  if (arq2 == NULL) {
    printf("ERRO NO ARQUIVO DE SAIDA\n");
    exit(1);
  }

  //empilharElementos(&c, '1',contaTemp, arq2);
  while ((caractere = fgetc(arq1)) != EOF) {
    printf("Caractere: %c\n\n", caractere);
    if (caracterValido(caractere)) {
      empilharElementos(&c, caractere, arq2);
      imprimePilha(&c);
    }
    if (operacaoValida(caractere)) {
      desempilhaInstrucoes(&c, arq2, caractere, &contaTemp);
      imprimePilha(&c);
    }
    if (estaVazia(&c)) {
      break;
    }
  }
  fclose(arq1);
  fclose(arq2);
  return 0;
}
