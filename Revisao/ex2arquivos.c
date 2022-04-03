/*ex1ponteiro.c
@author Andrei Fernandes Zani
@date 15/11/2021
@brief Fa¸ca um programa que receba do usu´ario um arquivo texto. Crie outro
arquivo
texto de sa´ıda contendo o texto do arquivo de entrada original, por´em
substituindo todas as vogais pelo
caractere ‘*’. Al´em disso, mostre na tela quantas linhas esse arquivo possui.
Dentro do programa fa¸ca
o controle de erros, isto ´e, insira comandos que mostre se os arquivos foram
abertos com sucesso, e caso
contr´ario, imprima uma mensagem de erro encerrando o programa.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
  int caractere;
  int contaLinha = 0;
  char arquivoTexto[101];

  FILE *arq1 = fopen("E1.txt","r");
  if (arq1 == NULL) {
    printf("Erro arquivo de entrada\n");
    exit(1);
  }
  FILE *arq2 = fopen("S1.txt","w");
  if (arq2 == NULL) {
    printf("Erro arquivo de saida\n");
    exit(1);
  }
  while((caractere = fgetc(arq1)) != EOF){
    if (caractere == '\n') {
      contaLinha++;
    }
    if(caractere == 'a' || caractere == 'e' || caractere == 'i' || caractere == 'o' || caractere == 'u'){
      fputc('*',arq2);
    }
    else{
      fputc(caractere, arq2);
    }
  }
  printf("Linhas no arquivo: %d\n",contaLinha);

  fclose(arq1);
  fclose(arq2);
}
