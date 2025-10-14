#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constantes globais

#define MAX_TERRITORIOS 5

//definição da struct

struct Territorio {
    char nome [30];
    char cor [10];
    int tropas;
};

// função para limpar o buffer de entrada

void LimparBufferDeEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//FUNÇÃO PRINCIPAL 
int main() {
    //Criando um vetor para o jogo
    struct Territorio mundo[MAX_TERRITORIOS];
    int TotalTerritorios = 0; //variável para armazenar o número de territórios

    //Laço do menu
    do{
        //Exibição do MENU
        printf("==========================================================\n");
        printf("\nVamos cadastrar os 5 territórios iniciais do nosso mundo.\n");
        printf("Cadastrando Território\n");
        printf("0 -> SAIR\n");
        printf("Escolha uma das opções: ");
    }
    
}