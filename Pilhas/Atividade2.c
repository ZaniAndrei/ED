#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



/*construir um compilador que recebe uma expressão escrita em Notação Pos-fixa
ex: a*b + c -> a b * c +   a*(b+c) -> a b c + *   (a+b)*c -> a b + c *
(a+b)*(cd)->a b + c d + *
EX:
AB*C+ = LDR B        carrega B
        LDR A        carrega A
        MULT B A     multiplica B e A
        STR TEMP1    armazena em uma variavel temp1
        LDR C        carrega C
        LDR TEMP1    carrega temp1
        ADD C TEMP1  soma C em temp1
*/

typedef PtrNoPilha Nopilha;

//struct da pilha dos elementos
typedef struct{
  char expressao;
  char topo;
}








int main(int argc, char const *argv[]) {
  printf("SEX\n");
  return 0;
}
