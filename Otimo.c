#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * Algoritmo otimo para substituicao de paginas
 */

//Declaracao de variaveis globais
FILE *IN;
int FRAMES;
int PAGINAS = 0; //A definir
int DESLOCAMENTO = 0;//A definir

int main(int argc, char *argv[]){

	if (argc < 3){
		printf ("Argumentos Insuficientes\n");
		return 1;
	}

	if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "/f") == 0 || strcmp(argv[1], "-F") == 0 || strcmp(argv[1], "/F") == 0){ //Opcao Frames
    FRAMES = atoi(argv[3]); //Converte o tamanho solicitado da unidade para inteiro
    if (FRAMES <= 0){
      printf("Quantidade invalida. Deve ser maior que zero\n");
      return 1;
    }
	}

	IN = fopen(argv[2], "r");

	if (IN == NULL){
      printf("Erro, Arquivo invalido");
      return 1;
  }

  return 0;
}
