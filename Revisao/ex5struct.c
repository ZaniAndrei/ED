/*ex1ponteiro.c
@author Andrei Fernandes Zani
@date 15/11/2021
@brief   Defina um tipo abstrato de dados que ir´a representar bandas de m´usica.
Essa estrutura deve ter o nome da banda, que tipo de m´usica ela toca, o n´umero de integrantes, e em que
posi¸c˜ao do ranking essa banda est´a dentre as suas 5 bandas favoritas.
a) Crie uma fun¸c˜ao para preencher as 5 estruturas de bandas criadas no exemplo passado;
b) Ap´os criar e preencher, exiba todas as informa¸c˜oes das bandas/estruturas;
c) Crie uma fun¸c˜ao que pe¸ca ao usu´ario um n´umero de 1 at´e 5. Em seguida, seu programa deve exibir
informa¸c˜oes da banda cuja posi¸c˜ao no seu ranking ´e a que foi solicitada pelo usu´ario.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nomeBanda[5][21];
  char tipoBanda[5][21];
  int numeroIntegrantes[5];
  int posicaoRanking[5];
}Banda;

int criabanda(Banda* banda){
  //cria e preenche
  for (size_t i = 0; i < 5; i++) {
    setbuf(stdin, NULL);

    printf("Digite o nome da banda %d: ",i+1);
    fgets(banda->nomeBanda[i],21,stdin);
    banda->nomeBanda[i][strcspn(banda->nomeBanda[i],"\n")] = '\0';
    setbuf(stdin,NULL);

    printf("Digite o tipo da banda %d: ",i+1);
    fgets(banda->tipoBanda[i],21,stdin);
    banda->tipoBanda[i][strcspn(banda->tipoBanda[i],"\n")] = '\0';
    setbuf(stdin,NULL);

    printf("Digite o numero de integrantes da banda %d: ",i+1);
    scanf("%d",&banda->numeroIntegrantes[i]);

    printf("Digite a posicao no ranking %d: ",i+1);
    scanf("%d",&banda->posicaoRanking[i]);
    printf("\n");
  }
  for (size_t i = 0; i < 5; i++) {
    printf("Nome da banda %d: %10s\n", i+1, banda->nomeBanda[i]);
    printf("Tipo da banda %d: %10s\n", i+1, banda->tipoBanda[i]);
    printf("Numero de integrantes da banda %d: %10d\n", i+1, banda->numeroIntegrantes[i]);
    printf("Ranking da banda %d: %10d\n", i+1, banda->posicaoRanking[i]);
    printf("\n");
  }

}

int rankingBusca(Banda* banda){
  int numeroBusca;
  printf("Digite o ranking da banda(1 a 5): ");
  scanf("%d",&numeroBusca);
    for (size_t i = 0; i < 5; i++) {
      printf("Entrei no for!\n");
      printf("%d\n", banda->posicaoRanking[i]);
      if (banda->posicaoRanking[i] == numeroBusca) {
        printf("Nome da banda : %10s\n", i+1, banda->nomeBanda[i]);
        printf("Tipo da banda : %10s\n", i+1, banda->tipoBanda[i]);
        printf("Numero de integrantes da banda : %10d\n", i+1, banda->numeroIntegrantes[i]);
        printf("Ranking da banda : %10d\n", i+1, banda->posicaoRanking[i]);
        printf("\n");
        exit(0);
        }
        else{
          continue;
      }
      }
  }


int main(int argc, char const *argv[]) {
  Banda banda;
  criabanda(&banda);
  rankingBusca(&banda);
  return 0;
}
