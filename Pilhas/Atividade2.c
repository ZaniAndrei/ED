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
bool letraValida(char caracter){
  if ((caracter >= 65 && caracter <= 122) || (caracter == 42 ||
    caracter == 43 || caracter == 45 || caracter == 47 )){
    return true;
  }else{
    printf("Caracter (%c) invalido\n", caracter);
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

void empilharElementos(PilhaDinamica *compilador, char caracter){
  //só ira empilhar os elementos se eles forem validos(funções retornam true)
  if (operacaoValida(caracter) || letraValida(caracter)) {
    PtrNoPilha aux = malloc(sizeof(NoPilha));
    aux->instrucao = caracter;
    aux->proximo = compilador->topo;
    compilador->topo = aux;
    compilador->qtde++;
  }
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

void desempilhaInstrucoes(PilhaDinamica *compilador, FILE* arq){
  PtrNoPilha aux;
  aux = pilha->topo;
  pilha->topo = pilha->topo->proximo;
  free(aux);
  pilha->qtde--;
}



int main(int argc, char const *argv[]) {
  PilhaDinamica c;
  char caractere;
  iniciarPilha(&c);

  FILE *arq1 = fopen("entrada.txt", "r");
  if (arq1 == NULL) {
    printf("ERRO NO ARQUIVO DE LEITURA\n");
    exit(1);
  }
  while (caractere != ' ') {
    fscanf(arq1, "%c", &caractere);
    printf("Caractere: %c\n\n", caractere);
    empilharElementos(&c, caractere);
    imprimePilha(&c);
  }
  fclose(arq1);

  while (!estaVazia(&c)) {
    desempilhaInstrucoes(&c, arq2);
  }

  FILE *arq2 = fopen("saida.txt", "w");
  if (arq2 == NULL) {
    printf("ERRO NO ARQUIVO DE SAÍDA\n");
    exit(1);
  }


  return 0;
}
