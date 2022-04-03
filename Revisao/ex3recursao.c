/*ex1ponteiro.c
@author Andrei Fernandes Zani
@date 15/11/2021
@brief Escreva uma fun¸c˜ao recursiva para calcular o valor de um n´umero
inteiro de base
x elevada a um expoente inteiro y.

*/
#include <stdio.h>
#include <stdlib.h>
int xAux = 1;
int numeroRecursao(int x, int y){
  if(y == 0){
    return xAux;
  }
  else{
    xAux *= x;
    numeroRecursao(x, y - 1);
    }
  }


int main(){
  int x = 5;
  int y = 4;
  int valorFuncao;
  valorFuncao = numeroRecursao(x,y);
  printf("X elevado a Y e: %d\n",valorFuncao);

}
