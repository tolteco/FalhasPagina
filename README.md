# Falhas de Pagina
## 2º. Trabalho de Sistemas Operacionais.
### Objetivo
Determinar o número de falhas de páginas de diferentes algoritmos de substituição
de páginas.
Dados de entradas serão logs de acesso à memória obtidos de:

http://traces.cs.umass.edu/index.php/CpuMem/CpuMem.

O trace descompactado em formato texto está disponibilizado no arquivo:

http://www.inf.unioeste.br/~marcio/SO/traces.zip

O formato do trace é um endereço de 32 bits representado em hexadecimal. É importante notar
que cada linha do arquivo de entrada contém **um acesso a memória e não o endereço da
página**. Para determinar a página acessada será necessário construir o *“reference string”*
considerando o tamanho da página, conforme apresentado em sala de aula.
Cada equipe deverá definir qual o tamanho da página, dentro do espaço de endereçamento
lógico de 32 bits. Por exemplo, se a equipe definir que cada página tem 4096 bytes, significa que
12 bits são utilizados para o deslocamento e consequentemente 20 bits são utilizados para o
número da página.
O usuário poderá informar o número de frames, e como resultado o simulador deverá informar
**no mínimo** o número de falhas de páginas e também o tempo de simulação.
### Algoritmos de falhas de páginas a serem simulados:
- Ótimo
- LRU pilha

## Desenvolvimento
### Chamada
```
[programa] [opção] arquivo [frames]
frames  : Quantidade de frames
programa:
        Windows: Otimo.exe | LRUPilha.exe
        Linux:   ./Otimo.x | ./LRUPilha.x
opção   :
        /f : Entrada normal com o numero de frames
        /i : Imprime o estado dos frames a cada iteração (Não imprime tempo nem falhas de página)
```
### LRUPilha
Estrutura da pilha:
```
typedef struct nodo{
    int info; //Pagina
    struct nodo* ant;
    struct nodo* prox;
}NODO;
typedef NODO* LISTAD;

//Variaveis globais lista
NODO* lista; //comeco da lista (posicao da pilha a serem inseridos novos nos)
NODO* listaF; //fim da lista (posicao de onde saem os nos para falhas de pagina)
```
Método `acesso_a_pagina(int [pagina a ser acessada])` deve ser usado para iteragir com a pilha. Próprio método insere elementos, remove e produz falhas de página.

### Otimo
Método `aloca_frames()` aloca vetor F com a FRAMES posições e atribui a todas as posições -1


### Ambos
- Método `ledados()` lê arquivo passado por parâmetro - máximo de 11.000.000 (onze milhões) de entradas.
- Método `hexaint()` Traduz string lida (hexadecimal) para valor decimal, retorna numero da página a ser acessada.
