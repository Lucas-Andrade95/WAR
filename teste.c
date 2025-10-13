#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constantes globais

#define MAX_LIVROS 50
#define TAM_STRING 100

//definição da struct

struct Livro {
    char nome [TAM_STRING];
    char autor [TAM_STRING];
    char editora [TAM_STRING];
    int edicao;
};

// função para limpar o buffer de entrada

void LimparBufferDeEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função Main
int main() {
    struct Livro biblioteca[MAX_LIVROS];
    int totallivros = 0;
    int opcao;
    // --- Laço principal do Menu --- 
    do {
        //Exibe o MENU
        printf("____________THE LIBRARY - PARTE 1__________\n");
        printf("1 -> Cadastrar novo livro\n");
        printf("2 -> Listar todos os livros\n");
        printf("0 -> SAIR\n");
        printf("Escolha uma das opções: ");

        scanf("%d", &opcao);
        LimparBufferDeEntrada();
        switch (opcao)
        {
        case 1: // CADASTRO DE LIVRO
            prinf("--Cadastro de novo livro--\n");

            if (totallivros < MAX_LIVROS) {
                printf("Nome do Livro: ");
                fgets(biblioteca[totallivros].nome, TAM_STRING, stdin);
                
                printf("Nome do Autor: ");
                fgets(biblioteca[totallivros].autor, TAM_STRING, stdin);

                printf("Nome da Editora: ");
                fgets(biblioteca[totallivros].editora, TAM_STRING, stdin);

                biblioteca[totallivros].nome[strcpn(biblioteca[totallivros].nome, "\n")] = 
                biblioteca[totallivros].autor[strcpn(biblioteca[totallivros].autor, "\n")] = 
                biblioteca[totallivros].editora[strcpn(biblioteca[totallivros].editora, "\n")] = 

                printf("Digite a edição: ");
                scanf("%d", &biblioteca[totallivros].edicao);
                LimparBufferDeEntrada();

                totallivros++;

                printf("\nLivro cadastrado com sucesso! \n");


            } else {
                printf("Biblioteca cheia! Não é possível cadastrar mais livros.\n");
            }
            printf("\nPressione enter para continuar ...");
            getchar(); // Pausa para o usuário ler a msg antes de voltar ao menu.
            break;

        case 2: //INICIA A LISTAGEM DOS LIVROS CADASTRADOS
            printf("---- Livros cadastrados ----\n\n");

            if (totallivros == 0) {
                printf("Nenhum livro cadastrado :/ \n");
            } else {
                for ( int i = 0; i < totallivros; i++) {
                    printf(" ------------------------------ \n");
                    printf("Livro %d")
                }
            }
        
        default:
            break;
        }
    };
}