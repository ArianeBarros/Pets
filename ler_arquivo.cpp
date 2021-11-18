#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

int num;
char linha[20];
FILE *arq;

if ((arq= fopen("Arquivo.txt", "r+"))==NULL){
  printf("Arquivo não existente. Criacao do arquivo\n");
  arq= fopen ("Arquivo.txt", "w+");

  printf("Digite um numero para inserir no arquivo:");
  scanf("%d",&num);
  fprintf(arq, "%d", num);
  fprintf(arq,"%c", ' ');
  printf("Digite uma palavra para inserir no arquivo:");
  scanf("%s",linha);
  fprintf(arq, "%s", linha);

}
   else{
     printf("O arquivo ja existe\n");
     fscanf(arq,"%d", &num);
     printf("Numero lido do arquivo: %d\n", num);
     fscanf(arq,"%s", linha);
     printf("Palavra lida do arquivo: %s\n", linha);

   }


fclose(arq);
}
