#ifndef PILHA_H
#define PILHA_H
#include <stdio.h>

//estrutura para representar uma posição no labirinto
typedef struct{
    int x, y;
}Posicao;

//estrutura para representar o personagem
typedef struct{
    int x, y;
}Personagem;

//estrutura para representar um nó da pilha
typedef struct no{
    Personagem per;
    struct no *prox;
}No;

//pilha para armazenar os nós
typedef struct{
    No *cabeca;
    int comprimento;
}Pilha;

//função para inicializar a pilha
void inicializar(Pilha *p);

//função para empilhar um nó
void empilhar(Personagem personagem, Pilha *p);

//função para desempilhar um nó
void desempilhar(Pilha *p);

//função para verificar se a pilha esta vazia
int vazia(Pilha *);

//função para verificar se uma posição é valida no labirinto
int valido(int x, int y, int **matrizL, int n);

//função para encontrar o caminho no labirinto usando Backtracking
int encontrarCaminho(Posicao ini, Posicao final, int **matrizL, int n);

//função para criar a matriz do labirinto a partir de um arquivo
int **criarMatrizL(const char *nome, int *n, Posicao *ini, Posicao *final);

//função para criar a matriz do rastro do labirinto
int **criaMatrizR(int n);

//função para imprimir o personagem andando ou retrocedendo na tela
void imprimirPersonagem(int n, Posicao ini, Personagem personagem, int **rastro, int **matrizL);

//função para liberar a memoria alocada para a matriz do rastro do labirinto
void liberarMatrizR(int **rastro, int n);

//função para liberar a memoria alocada para a matriz do labirinto
void liberarMatrizL(int **matrizL, int n);

#endif