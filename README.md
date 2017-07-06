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
frames  : Quantidade de frames (necessario opção /f)
programa: 
        Windows: Otimo.exe | LRUPilha.exe
        Linux:   ./Otimo.x | ./LRUPilha.x
opção   :
        FALTA ESCREVER
        /f : Considera o número de frames fornecido
```
