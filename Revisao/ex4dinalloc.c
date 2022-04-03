/*ex1ponteiro.c
@author Andrei Fernandes Zani
@date 15/11/2021
@brief  Fa¸ca um programa que leia um valor N e crie dinamicamente um
vetor com essa quantidade de elementos. Em seguida, passe esse vetor para uma
 fun¸c˜ao que vai ler os
elementos desse vetor. Depois, no programa principal, imprima os valores do
vetor preenchido. Al´em disso,
antes de finalizar o programa, lembre-se de liberar a ´area de mem´oria alocada
 para armazenar os valores do
vetor
*/
#include <stdio.h>
#include <stdlib.h>
int* preencheVetor(int n, int* vetor){
  for (size_t i = 0; i < n; i++) {
    printf("Digite o elemento [%d]: \n",i);
    scanf("%d",&vetor[i]);
  }
  return vetor;
}

int main(){
  int n;
  int* valor;
  printf("Digite o tamanho do vetor: ");
  scanf("%d",&n);

  int* vetor = malloc(sizeof(int) * n);

  valor = preencheVetor(n, vetor);
  for (size_t i = 0; i < n; i++) {
    printf("Elemento[%d]:%d\n", i, *(valor + i));
  }

}
