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

////////////////////////////////////////////VERIFICA FALHA DE PAGINA
//Variaveis globais este setor
int fa, J, I, K; //fa e o numero de falhas de pagina

int falhapagina(){ //Verifica falhas de pagina
    fa = 0;
    J = 0;
    I = 0;
    K = 0;
    int i;
    while(REQ[J] != -1){
        if(K != FRAMES){ //Coloca conteudo em F ate q fique cheio
            while(REQ[J] == F[I] || F[I] != -1){
                if(REQ[J] == F[I]){
                    J++;
                }else{
                    I++;
                }
            }
            if(F[I] == -1){
                F[I] = REQ[J];
                J++;
                fa++;
                I = 0;
            }
            K++;
        }else{ //Inicio do tratamento apos vetor F estar cheio
            while(REQ[J] != F[I] && I != FRAMES){
                I++;
            }
            if(REQ[J] == F[I]){
                J++;
                I = 0;
            }else{
                oraculo(); //Verifica o futuro
                F[I] = REQ[J];
                fa++;
                I = 0;
                J++;
            }
        }
    }
    return 0;
}

////////////////////////////////////////////VERIFICA A LISTA (FUTURO)
//Variaveis globais este setor
int O; //"O" e o novo contador usado em REQ para preservar o valor de J

int oraculo(){ //Verifica o futuro
    int C, k, i;
    int AUX[FRAMES];
    C = 0;
    O = J+1;
    k = FRAMES - 1;
    for (i = 0; i < FRAMES; i++){
		AUX[i] = 0;
	}
    while(REQ[O] != -1 || C != k){
        while(REQ[O] != F[I] && I != FRAMES){
            if(REQ[O] == -1){
                i = 0;
                while(AUX[i] == 1){
                    i++;
                }
                I = i;
                return 0;
            }else{
                I++;
            }
        }
        if(REQ[O] == F[I]){
            AUX[I] = 1;
            I = 0;
            C++;
            O++;
        }else{
            O++;
            I = 0;
        }
    }
    i = 0;
    while(AUX[i] == 1){
        i++;
    }
    I = i;
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

int falhapagina2(){ //Verifica falhas de pagina com impressão
    fa = 0;
    J = 0;
    I = 0;
    K = 0;
    int i;
    printf("Primeiras %i paginas:\n", FRAMES);
    while(REQ[J] != -1){
        if(K != FRAMES){ //Coloca conteudo em F ate q fique cheio
            while(REQ[J] == F[I] || F[I] != -1){
                if(REQ[J] == F[I]){
                    J++;
                }else{
                    I++;
                }
            }
            if(F[I] == -1){
                F[I] = REQ[J];
                J++;
                fa++;
                I = 0;
            }
            for(i=0;i<FRAMES;i++){
                printf("|%i", F[i]);
            }
            K++;
            printf("\n");
        }else{ //Inicio do tratamento apos vetor F estar cheio
            while(REQ[J] != F[I] && I != FRAMES){
                I++;
            }
            if(REQ[J] == F[I]){
                printf("Nao houve falha de pagina -- REQ[J]=%i\n", REQ[J]);
                J++;
                I = 0;
            }else{
                oraculo2(); //Verifica o futuro
                printf("Nova pagina inserida ");
                F[I] = REQ[J];
                fa++;
                I = 0;
                J++;
            }
            for(i=0;i<FRAMES;i++){
                printf("|%i", F[i]);
            }
            printf("\n");
        }
    }
    printf("\nFalhas geradas: %i\n", fa);
    return 0;
}

////////////////////////////////////////////VERIFICA A LISTA (FUTURO) com impressão

int oraculo2(){ //Verifica o futuro
    int C, k, i;
    int AUX[FRAMES];
    C = 0;
    O = J+1;
    k = FRAMES - 1;
    I = 0;
    for (i = 0; i < FRAMES; i++){
		AUX[i] = 0;
	}
    while(REQ[O] != -1 || C != k){
        while(REQ[O] != F[I] && I != FRAMES){
            if(REQ[O] == -1){
                i = 0;
                while(AUX[i] == 1){
                    i++;
                }
                I = i;
                return 0;
            }else{
                I++;
            }
        }
        if(REQ[O] == F[I]){
            AUX[I] = 1;
            I = 0;
            C++;
            O++;
        }else{
            O++;
            I = 0;
        }
    }
    i = 0;
    while(AUX[i] == 1){
        i++;
    }
    I = i;
    return 0;
}

int main(int argc, char *argv[]){
    double T;
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
      return 1;
  }
	ledados();

	if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "/f") == 0 || strcmp(argv[1], "-F") == 0 || strcmp(argv[1], "/F") == 0){ //Opcao convencional
		clock_t ini = clock();
		falhapagina();
		clock_t fim = clock();
		T = ((double)(fim - ini)) / CLOCKS_PER_SEC;
		printf("Falhas geradas: %i\nTempo necessario para executar: %lf\n", fa, T);
  }

	if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "/i") == 0 || strcmp(argv[1], "-I") == 0 || strcmp(argv[1], "/I") == 0){ //Opcao impressao paginas
        falhapagina2();
  }

  return 0;
}
