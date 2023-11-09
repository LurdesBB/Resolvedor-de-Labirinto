#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pilha.h"

//função para inicializar a pilha
void inicializar(Pilha *p)
{
    p->cabeca = NULL;
}

//função para empilhar um nó
void empilhar(Personagem personagem, Pilha *p)
{
    No *noNovo = (No *)malloc(sizeof(No));
    noNovo->per = personagem;
    noNovo->prox = p->cabeca;
    p->cabeca = noNovo;
}

//função para desempilhar um nó
void desempilhar(Pilha *p)
{
    if(p->cabeca != NULL){
        No *aux = p->cabeca;
        p->cabeca = p->cabeca->prox;
        free(aux);
    }
}

//função para verificar se a pilha esta vazia
int vazia(Pilha *p)
{
    return p->cabeca == NULL;
}

//função para verificar se uma posição é valida no labirinto
int valido(int x, int y, int **matrizL, int n)
{
    return n >= 0 && x < n && y >= 0 && y < n && (matrizL[x][y] == 0 || matrizL[x][y] == 3);
}

//função para encontrar o caminho no labirinto usando Backtracking
int encontrarCaminho(Posicao ini, Posicao final, int **matrizL, int n)
{
    Pilha p;

    inicializar(&p);

    int **rastro = criaMatrizR(n);

    int proximo_x, proximo_y;

    Personagem personagem;
    personagem.x = ini.x;
    personagem.y = ini.y;

    empilhar(personagem,&p);

    int Dx[] = {-1, 0, 1, 0}; //deslocamento nas direções cima, direita, baixo, esquerda
    int Dy[] = {0, 1, 0, -1};

    while(!vazia(&p)){

        personagem = p.cabeca->per;

        Posicao posicao;
        posicao.x = personagem.x;
        posicao.y = personagem.y;

        if(posicao.x == final.x && posicao.y == final.y){ //chegamos ao destino

            printf("\nCaminho correto: ");
            No *atual = p.cabeca;

            while(atual != NULL){

                Personagem per = atual->per;

                printf("(%d,%d) ",per.x,per.y);
                atual = atual->prox;
            }
            liberarMatrizR(rastro,n); //função para liberar a memória alocada para a matriz do rastro do labirinto
            return 1;
        }

        int direcao = 0;
        int movimento = 0;

        while(direcao<4){ //faz enquanto tiver direções para ir

            proximo_x = posicao.x + Dx[direcao];
            proximo_y = posicao.y + Dy[direcao];

            if(valido(proximo_x,proximo_y,matrizL,n)){ //move para a próxima posição válida

                personagem.x = proximo_x;
                personagem.y = proximo_y;

                empilhar(personagem,&p);

                matrizL[proximo_x][proximo_y] = -1; //marca como visitado
                rastro[proximo_x][proximo_y] = 1;    //marca o rastro
                movimento = 1;

                imprimirPersonagem(n,ini,personagem,rastro,matrizL); //função para imprimir o personagem andando ou retrocedendo na tela

                break;
            }
            direcao++;
        }

        if(!movimento){ //não há movimentos validos a partir desta posição, então ele ira retroceder

            matrizL[posicao.x][posicao.y] = -1; //marca como visitado

            desempilhar(&p);

            imprimirPersonagem(n,ini,personagem,rastro,matrizL); //função para imprimir o personagem andando ou retrocedendo na tela

            rastro[posicao.x][posicao.y] = 0; //atualiza o rastro na posição anterior
        }
    }
    printf("Nao ha caminho possivel.\n"); //não foi encontrado um caminho

    liberarMatrizR(rastro,n); //função para liberar a memória alocada para a matriz do rastro do labirinto

    return 0;
}

//função para criar a matriz do labirinto a partir de um arquivo chamado "file"
int **criarMatrizL(const char *nome, int *n, Posicao *ini, Posicao *final)
{
    FILE *file = fopen(nome,"r");

    if(file == NULL){ //verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fscanf(file,"%d",n); //pega o primeiro valor que esta no arquivo, que no caso é o valor que indica o tanto de linhas e colunas

    int **matrizL = (int **)malloc(*n * sizeof(int *)); //aloca memoria para a matriz labirinto de acordo com o tanto de linhas e colunas que foi pré determinado
    for(int i=0; i<*n; i++){
        matrizL[i] = (int *)malloc(*n * sizeof(int)); //matrizL é o abreviamento de matriz labirinto
    }

    for (int i = 0; i<*n; i++){ //loop para passar a matriz do arquivo para a matriz labirinto
        for(int j=0; j < *n; j++) {
            fscanf(file,"%d",&matrizL[i][j]);
            if(matrizL[i][j] == 2){ //pega o começo do labirinto
                ini->x = i;
                ini->y = j;
            } else if(matrizL[i][j] == 3){ //pega o final do labirinto
                final->x = i;
                final->y = j;
            }
        }
    }
    fclose(file);

    return matrizL;
}

//função para criar a matriz do rastro do labirinto
int **criaMatrizR(int n)
{
    int **rastro = (int **)malloc(n * sizeof(int *));
    for(int i=0; i<n; i++){
        rastro[i] = (int *)malloc(n * sizeof(int));
    }

    return rastro;
}

//função para imprimir o personagem andando ou retrocedendo na tela
void imprimirPersonagem(int n, Posicao ini, Personagem personagem, int **rastro, int **matrizL)
{
    for(int i=0; i<n; i++){ //imprimi o personagem
        for(int j=0; j<n; j++){
            if(i == personagem.x && j == personagem.y){
                    printf("o ");;
            }else if(rastro[i][j] == 1){
                    printf(". ");
            }else if(matrizL[i][j] == 1){
                    printf("# ");
            }else if(matrizL[i][j] == 0){
                    printf("  ");
            }else if(matrizL[i][j] == 3){
                    printf("@ ");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");

    usleep(200000); //faz o labirinto ser imprimido na tela de acordo com o tempo colocado na função
}

//função para liberar a memória alocada para a matriz do rastro do labirinto
void liberarMatrizR(int **rastro, int n)
{
    for(int i=0; i<n; i++){
        free(rastro[i]);
    }
    free(rastro);
}

//função para liberar a memória alocada para a matriz do labirinto
void liberarMatrizL(int **matrizL, int n)
{
    for(int i=0; i<n; i++){
        free(matrizL[i]);
    }
    free(matrizL);
}