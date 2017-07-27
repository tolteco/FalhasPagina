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

////////////////////////////////////////////VERIFICA A LISTA (FUTURO)
//Variaveis globais este setor
int O; //O = contador usado em REQ para preservar o valor de J
int FA, J, I, K; //FA = numero de Falhas de pagina

void oraculo(){ //Verifica o futuro
  int C, k, i;
  int AUX[FRAMES];
  C = 0;
  O = J + 1; //Continua para frente da posicao atual
  k = FRAMES - 1;
  for (i = 0; i < FRAMES; i++){
		AUX[i] = 0;
	}
	i = 0;
  while(REQ[O] > -1 && C < k){ //Enquanto nao estourar o vetor de requisicoes ou a quantidade de paginas -1
		//printf("Requisicao: %d, O = %d\n", REQ[O], O);
		while (i < FRAMES && REQ[O] != F[i]){ //Procurando para marcar
			//printf("Posicao: [%d]\n", i);
			i++;
		}
		//printf("i = %d\n", i);
		if (i == FRAMES){ //Estourou
			O++;
			i = 0;
		} else {
			if (AUX[i] == 0){
				AUX[i] = 1;
				i = 0;
			}
			C++;
			O++;
		}
		//printf("C = %d\n", C);
	}
	i = 0;
  while(AUX[i] == 1){
    i++;
  }
  I = i;
	//printf("Oraculo diz: I = %d\n", I);
  return;
}

////////////////////////////////////////////VERIFICA FALHA DE PAGINA

int falhapagina(){ //Verifica Falhas de pagina
  FA = 0;
  J = 0;
  I = 0;
  K = 0;
  int i;
  while(REQ[J] != -1){
		if (J%10000 == 0){
			printf("Requisicao %d\n", J);
		}
	  if(K != FRAMES){ //Coloca conteudo em F ate q fique cheio
			//printf("if\n");
	  	while(REQ[J] == F[I] || F[I] != -1){
	    	if(REQ[J] == F[I]){
	      	J++;
	      } else {
	      	I++;
	      }
	    }
	  	if(F[I] == -1){
	    	F[I] = REQ[J];
	      J++;
	      FA++;
	      I = 0;
	    }
	    K++;
			//printf("K = %d", K);
	  } else { //Inicio do tratamento apos vetor F estar cheio
			//printf("else\n");
			while(REQ[J] != F[I] && I != FRAMES-1){
	    	I++;
	    }
	    if(REQ[J] == F[I]){ //Se o elemento foi encontrado na lista (consulta)
	    	J++;
	      I = 0;
	    } else {
	    	oraculo(); //Verifica o futuro
	      F[I] = REQ[J];
	      FA++;
	      I = 0;
	      J++;
			}
	  }
	}
  return 0;
}

void ledados(){
	int i, j = 0;
	while (!feof(IN)){
		fscanf (IN, "%s\n", &U);
		i = hexaint();
        REQ[j] = i; //Vetor de paginas
        j++;
	}
	REQ[j] = -1;
}

void imprimeframes(){
	int i;
	for (i = 0; i < FRAMES; i++){
		if (F[i] != -1){
			printf("Pagina->%i\n", F[i]);
		}
  }
}

////////////////////////////////////////////Funcoes ligadas a impressao
int falhapagina2(){ //Verifica Falhas de pagina com impressao
	FA = 0;
	J = 0;
	I = 0;
	K = 0;
	int i;
	while(REQ[J] != -1){
		if(K != FRAMES){ //Coloca conteudo em F ate q fique cheio
			while(REQ[J] == F[I] || F[I] != -1){
				if(REQ[J] == F[I]){
					printf("\nConsulta a pagina\t\t\t%d\n", REQ[J]);
					J++;
				}else{
					I++;
				}
			}
			if(F[I] == -1){
				printf("\nOcorreu uma falha de pagina na pagina\t%d\n", REQ[J]);
				F[I] = REQ[J];
				J++;
				FA++;
				I = 0;
			}
			imprimeframes();
			K++;
			printf("\n");
		} else { //Inicio do tratamento apos vetor F estar cheio
			while(REQ[J] != F[I] && I != FRAMES){
				I++;
			}
			if(REQ[J] == F[I]){
				printf("\nConsulta a pagina\t\t\t%d\n", REQ[J]);
				J++;
				I = 0;
			}else{
				oraculo(); //Verifica o futuro
				printf("\nOcorreu uma falha de pagina na pagina\t%d\n", REQ[J], I);
				F[I] = REQ[J];
				FA++;
				I = 0;
				J++;
			}
			imprimeframes();
		}
	}
	printf("Falhas geradas: %d\n", FA);
	return 0;
}

int main(int argc, char *argv[]){
  double T;
	int Te;
	if (argc < 4){
		printf ("Argumentos Insuficientes\n");
		return 1;
	}

	FRAMES = atoi(argv[3]); //Converte o tamanho solicitado da unidade para inteiro
	if (FRAMES <= 0){
		printf("Quantidade de frames invalida. Deve ser maior que zero\n");
		return 1;
	}
	Te = aloca_frames();
	if (Te == -1){
		printf ("Nao foi possivel alocar o vetor de frames");
		return 1;
	}

	IN = fopen(argv[2], "r");
	if (IN == NULL){
      return 1;
  }
	ledados();
	printf("Fim da leitura de disco\n");

	if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "/f") == 0 || strcmp(argv[1], "-F") == 0 || strcmp(argv[1], "/F") == 0){ //Opcao convencional
		clock_t ini = clock();
		falhapagina();
		clock_t fim = clock();
		T = ((double)(fim - ini)) / CLOCKS_PER_SEC;
		printf("Falhas geradas: %i\nTempo necessario para executar: %lf segundos\n", FA, T);
  }

	if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "/i") == 0 || strcmp(argv[1], "-I") == 0 || strcmp(argv[1], "/I") == 0){ //Opcao impressao paginas
    falhapagina2();
  }

  return 0;
}
