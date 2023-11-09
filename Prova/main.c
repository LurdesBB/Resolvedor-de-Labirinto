#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pilha.h"

//O codigo foi feito no Linux, não sei se muda algo se o senhor usar no Windows, mas só para questão de aviso caso algo de errado ou não rode, etc

int main()
{
    int n;
    Posicao ini, final;

    int **matrizL = criarMatrizL("labirinto.txt",&n,&ini,&final);

    if(encontrarCaminho(ini,final,matrizL,n)){
        printf("\nChegamos ao destino!\n");
    }else{
        printf("\nNao foi possivel encontrar um caminho!\n");
    }

    liberarMatrizL(matrizL,n); //libera a memória alocada para a matriz labirinto

    return 0;
}
