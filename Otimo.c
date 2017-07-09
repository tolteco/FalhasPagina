#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
 * Algoritmo otimo para substituicao de paginas
 */

//Declaracao de variaveis globais
FILE *IN;
int FRAMES = 6; //Quantidade total de frames
int PAGINA = 5; //A definir valor fixo - Quantidade de hexadecimais usados para enderecamento de paginas
int DESLOCAMENTO = 3;//A definir - Quantidade de hexadecimais usados para deslocamento
int OCUPADOS = 0; //Quantidade de frames ocupados
int REQ[11000000]; //Vetor com requisicoes do arquivo (onze milhoes de posicoes - 44Mb em memoria)
int *F;

////////////////////////////////////////////INICIO METODOS ITERACAO COM FRAMES
int aloca_frames(){ //Aloca um vetor F com a quantidade de frames
	int i;
	F = malloc (sizeof (int) * FRAMES); /* n is the length of the array */
	if (F == NULL ){
		return -1;
	}
	for (i = 0; i < FRAMES; i++){
		F[i] = -1;
	}
	return 0;
}

////////////////////////////////////////////FIM DOS METODOS DE ITERACAO COM FRAMES
////////////////////////////////////////////LEITURA E TRATAMENTO DE LEITURA
//Variaveis globais este setor
char U[10];

int hexaint(){
	int i, j, US, SUM = 0;
	US = strlen(U);
	if (US <= DESLOCAMENTO){
		return 0;
	}
	j = 4;
	for (i = 0; i < (US-DESLOCAMENTO); i++){
		if (U[i] == 'F'){
			SUM = (SUM + 15) << j;
		}
		if (U[i] == 'E'){
			SUM = (SUM + 14) << j;
		}
		if (U[i] == 'D'){
			SUM = (SUM + 13) << j;
		}
		if (U[i] == 'C'){
			SUM = (SUM + 12) << j;
		}
		if (U[i] == 'B'){
			SUM = (SUM + 11) << j;
		}
		if (U[i] == 'A'){
			SUM = (SUM + 10) << j;
		}
		if (U[i] == '9'){
			SUM = (SUM + 9) << j;
		}
		if (U[i] == '8'){
			SUM = (SUM + 8) << j;
		}
		if (U[i] == '7'){
			SUM = (SUM + 7) << j;
		}
		if (U[i] == '6'){
			SUM = (SUM + 6) << j;
		}
		if (U[i] == '5'){
			SUM = (SUM + 5) << j;
		}
		if (U[i] == '4'){
			SUM = (SUM + 4) << j;
		}
		if (U[i] == '3'){
			SUM = (SUM + 3) << j;
		}
		if (U[i] == '2'){
			SUM = (SUM + 2) << j;
		}
		if (U[i] == '1'){
			SUM = (SUM + 1) << j;
		}
		if (U[i] == '0'){
			SUM = (SUM + 0) << j;
		}
	}
	return SUM>>j;
}

void ledados(){
	int i, j = 0;
	while (!feof(IN)){
		fscanf (IN, "%s\n", &U);
		i = hexaint();
    REQ[j] = i;
    j++;
	}
}

////////////////////////////////////////////FIM LEITURA

int main(int argc, char *argv[]){
	if (argc < 4){
		printf ("Argumentos Insuficientes\n");
		return 1;
	}

	FRAMES = atoi(argv[3]); //Converte o tamanho solicitado da unidade para inteiro
	if (FRAMES <= 0){
		printf("Quantidade de frames invalida. Deve ser maior que zero\n");
		return 1;
	}
	aloca_frames();

	IN = fopen(argv[2], "r");
	if (IN == NULL){
      printf("Erro, Arquivo invalido");
      return 1;
  }
	ledados();

	if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "/f") == 0 || strcmp(argv[1], "-F") == 0 || strcmp(argv[1], "/F") == 0){ //Opcao convencional
		//Considerar nesse ponto apenas a simulacao, contagem de falhas e tempo
  }

	if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "/i") == 0 || strcmp(argv[1], "-I") == 0 || strcmp(argv[1], "/I") == 0){ //Opcao impressao de pilha
    //Considerar nesse ponto imprimir todas as vezes como os frames estao - Nesse nao vai tempo nem falhas (DEBUG MODE)
  }

  return 0;
}
