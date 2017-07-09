#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/**
* LRU Pilha para substituicao de paginas
*/

//Declaracao de variaveis globais
FILE *IN;
int FRAMES = 6; //Quantidade total de frames
int PAGINA = 5; //A definir valor fixo - Quantidade de hexadecimais usados para enderecamento de paginas
int DESLOCAMENTO = 3;//A definir - Quantidade de hexadecimais usados para deslocamento
int OCUPADOS = 0; //Quantidade de frames ocupados
int REQ[11000000]; //Vetor com requisicoes do arquivo (onze milhoes de posicoes - 44Mb em memoria)

////////////////////////////////////////////LISTA DUPLAMENTE ENCADEADA COMO PILHA DO METODO
typedef struct nodo{
    int info; //Pagina
    struct nodo* ant;
    struct nodo* prox;
}NODO;
typedef NODO* LISTAD;

//Variaveis globais lista
NODO* lista; //comeco da lista (posicao da pilha a serem inseridos novos nos)
NODO* listaF; //fim da lista (posicao de onde saem os nos para falhas de pagina)

void lista_cria(){
	listaF = NULL;
  lista = NULL;
}

void lista_insere(int val){
  NODO* p;
  NODO* q;
  p = listaF;
  NODO* novo = (NODO*) malloc(sizeof(NODO)); //Reserva um espaço para novo
  novo->info = val; //Atribui a novo, o valor passado
	OCUPADOS += 1;
  if (lista == NULL){
    novo->prox = NULL; //Poe o ponteiro para o novo apontando para o elemento anterior da lista
    novo->ant = NULL;
		listaF = novo;
    lista = novo;
		return;
  }
  if (p->prox == NULL){ //Se string so tem um valor
    p->prox = novo;
    novo->prox = NULL;
    novo->ant = p;
    lista = novo;
		listaF = p;
		return;
  }
	lista->prox = novo;
	novo->prox = NULL;
	novo->ant = lista;
	lista = novo;
}

void lista_imprime (){ //Varre e imprime
  NODO* p;
  if (listaF == NULL){
    printf("Lista Vazia\n");
		return;
  }
  for (p = listaF; p != NULL; p = p->prox){
    printf("Pagina->%i\n",p->info);
  }
}

void lista_remove (){ //Remove primeiro
  NODO* p;
  if (listaF == NULL){
    return;
  }
	p = listaF;
  listaF = listaF->prox;
	free(p);
	OCUPADOS -= 1;
}

void lista_apagar (){
  NODO* p;
  NODO* q;
  int U = 0;
  if (listaF == NULL){
    return NULL;
  }
  p = listaF;
  while(U == 0){
    q = p->prox;
    free(p);
    p = q;
    if (p == NULL)
      U = 1;
  }
}

NODO* lista_procura (int V){
  NODO* p;
  for (p=listaF; p!=NULL; p=p->prox){
		if (p->info == V){ //Compara os valores
			return p;
		}
  }
	return NULL; //Se ninguem encaixar
}

void lista_empurra(NODO* P){ //Empurra um elemento para o comeco da lista
	NODO* p;
	NODO* a;
	NODO* d;
	if (listaF->prox == NULL){ //Lista contem apenas um elemento
		return;
	}
	if (lista->info == P->info){ //Elemento ja esta na extremidade
		return;
	}
	if (listaF->info == P->info){ //Elemento estava a ser removido
		listaF = P->prox;
		listaF->ant = NULL;
		P->ant = lista;
		P->prox = NULL;
		lista->prox = P;
		lista = P;
		return;
	}
	a = P->ant;
	d = P->prox;
	a->prox = d;
	d->ant = a;
	lista->prox = P;
	P->ant = lista;
	P->prox = NULL;
	lista = P;
}

//ITERACAO COM LISTA POR MEIO DESTA FUNCAO
void acesso_a_pagina(int V){ //Acessa a pagina (mexe na pilha) V
	NODO* p;
	p = lista_procura(V);
	if (p == NULL){ //Ninguem retornado
		if (OCUPADOS == FRAMES){ //Todos os frames estiverem ocupados
			lista_remove();
			lista_insere(V);
		} else { //Tem espaco
			lista_insere(V);
		}
	} else { //Pagina na lista
		lista_empurra(p);
	}
}
////////////////////////////////////////////FIM DECLARACAO LISTA
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
	lista_cria();

	if (argc < 4){
		printf ("Argumentos Insuficientes\n");
		return 1;
	}

	FRAMES = atoi(argv[3]); //Converte o tamanho solicitado da unidade para inteiro
	if (FRAMES <= 0){
		printf("Quantidade de frames invalida. Deve ser maior que zero\n");
		return 1;
	}

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

  //Aqui devem ir os dados de impressao de tempo usado e falhas de pagina

  lista_apagar();
  return 0;
}
