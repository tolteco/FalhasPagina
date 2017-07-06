#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * Algoritmo otimo para substituicao de paginas
 */
 
//Declaracao de variaveis globais
FILE *IN;

int main(int argc, char *argv[]){
	
	if (argc < 3){
		printf ("Argumentos Insuficientes\n");
		return 1;
	}
	
	if ((strcmp(op[1], "-h") == 0) || (strcmp(op[1], "/h") == 0) || (strcmp(op[1], "/help") == 0) || (strcmp(op[1], "-help") == 0)){ //Opcao Help
      printf("Sistema de arquivos Cumulo V%d.%d\n\n Chamada:\n\n", SVER, MVER);
      printf("	NOME.x [unidade]\n");
      printf("  [unidade]    Unidade separada para a unidade (sda, sdb1, ...)\n");
      return 0;
    }
	
	if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "/f") == 0 || strcmp(argv[1], "-F") == 0 || strcmp(argv[1], "/F") == 0){ //Opcao Frames
		//Opcao de frames
	}
	
	IN = fopen(argv[2], "r");
	
	if (IN == NULL){
      printf("Erro, Arquivo invalido");
      return 1;
    }

    return 0;
}
