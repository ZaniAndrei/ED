/*ex1ponteiro.c
@author Andrei Fernandes Zani
@date 15/11/2021
@brief Um ponteiro pode ser usado para dizer a uma fun¸c˜ao onde ela deve
 depositar
o resultado de seus c´alculos. Escreva uma fun¸c˜ao que converta uma quantidade
de minutos na nota¸c˜ao
horas/minutos. A fun¸c˜ao recebe como parˆametro:
• um n´umero inteiro (totalMinutos); e
• os endere¸cos de duas vari´aveis inteiras, horas e minutos.
A fun¸c˜ao deve ent˜ao atribuir valores `as vari´aveis passadas por referˆencia,
 de modo que os valores atribu´ıdos
respeitem as seguintes condi¸c˜oes:
minutos < 60
60 ∗ horas + minutos = totalMinutos
Escreva tamb´em a fun¸c˜ao principal (main) que use a fun¸c˜ao desenvolvida.
*/
#include <stdio.h>
#include <stdlib.h>

int converteHora(int totalMinutos, int *horas, int *minutos){
  int calculoHora;
  int calculoMin;
  totalMinutos = 2131;

  calculoHora = totalMinutos / 60;
  calculoMin = totalMinutos % 60;
  *horas = calculoHora;
  *minutos = calculoMin;
  printf("%d h %d min\n",*horas,*minutos);
}

int main() {
  int totalMinutos;
  int *horas;
  int *minutos;
  converteHora(totalMinutos, &horas, &minutos);
  return 0;
}
