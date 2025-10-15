#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constantes globais

#define MAX_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

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
    int TotalTerritorios = 5; //variável para armazenar o número de territórios

    //Exibição do Cadastro
    printf("==========================================================\n");
    printf("\nVamos cadastrar os 5 territórios iniciais do nosso mundo.\n");

    //LOOP for para criar os territórios
    for ( int i = 0; i < TotalTerritorios; i++) {

        printf("\n--- Cadastrando Território %d ---\n", i + 1); 
        printf("\nNome do Território: ");
        fgets(mundo[i].nome, TAM_NOME, stdin);
                    
        printf("Cor do exército (ex: Azul, Verde): ");
        fgets(mundo[i].cor, TAM_COR, stdin);

        mundo[i].nome[strcspn(mundo[i].nome, "\n")] = '\0';
        mundo[i].cor[strcspn(mundo[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mundo[i].tropas);
        LimparBufferDeEntrada();

    }
    
    //Exibição do MENU
    printf("\nCadastro inicial concluído com sucesso!\n");
    printf("\n==========================================\n");
    printf("\n     MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("\n==========================================\n");

    //LOOP para Exibir os territórios
    for (int i = 0; i < TotalTerritorios; i++) {
        printf("\nTERRITÓRIO %d:\n", i + 1);
        printf(" - Nome: %s\n", mundo[i].nome);
        printf(" - Dominado por: Exército %s\n", mundo[i].cor);
        printf(" - Tropas: %d\n\n", mundo[i].tropas);
    }

    return 0;
}
