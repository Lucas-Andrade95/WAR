//PRÁTICA SISTEMA DE BIBLIOTECA PARTE 2
//FUNCIONALIDADE DE EMPRÉSTIMO E USO DE ALOCAÇÃO DINÂNIMCA
//ARRAYS DE LIVROS E EMPRÉSTIMOS SÃO ALOCADOS COM MALLOC/CALLOC
//NOVA STRUCT PARA EMPRÉSTIMO
//LIBERAÇÃO DE MEMÓRIA COM FREE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constantes globais

#define MAX_LIVROS 50
#define TAM_STRING 100
#define MAX_EMPRESTIMOS 100 //Quantidade máxima de empréstimos

//definição das structs

struct Livro {
    char nome [TAM_STRING];
    char autor [TAM_STRING];
    char editora [TAM_STRING];
    int edicao;
    int disponivel; // ADICIONAMOS ATRIBUTO "DISPONÍVEL" PARA STATUS -  1 PARA SIM 0 PARA NÃO
};

//STRUCT EMPRÉSTIMO
struct Emprestimo {
    int indiceLivro; //
    char nomeUsuario[TAM_STRING];
};

// função para limpar o buffer de entrada

void LimparBufferDeEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função Main
int main() {
    //ALOCAÇÃO DINÂMICA DE MEMÓRIA
    //Agora, em vez de arrays estáticos, usamos ponteiros.
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;
   
    //CALLOC PARA O ARRAY DE LIVROS
    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));

    //MALLOC PARA O ARRAY DE EMPRÉSTIMOS
    emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    //VERIFICANDO SE A ALOCAÇÃO DE MEMÓRIA FUNCIONOU CORRETAMENTE
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        return 1; 
    }

    int totallivros = 0;
    int totalemprestimos = 0;
    int opcao;
    // --- Laço principal do Menu --- 
    do {
        //Exibe o MENU
        printf("__________THE LIBRARY - PARTE 2__________\n");
        printf("1 -> Cadastrar novo livro\n");
        printf("2 -> Listar todos os livros\n");
        printf("3 - Realizar empréstimo\n");
        printf("4 - Listar empréstimos\n");
        printf("0 -> SAIR\n");
        printf("Escolha uma das opções: ");

        scanf("%d", &opcao);
        LimparBufferDeEntrada();
        switch (opcao) {

            case 1: // CADASTRO DE LIVRO
                printf("--Cadastro de novo livro--\n");

                if (totallivros < MAX_LIVROS) {
                    printf("Nome do Livro: ");
                    fgets(biblioteca[totallivros].nome, TAM_STRING, stdin);
                    
                    printf("Nome do Autor: ");
                    fgets(biblioteca[totallivros].autor, TAM_STRING, stdin);

                    printf("Nome da Editora: ");
                    fgets(biblioteca[totallivros].editora, TAM_STRING, stdin);

                    biblioteca[totallivros].nome[strcspn(biblioteca[totallivros].nome, "\n")] = '\0';
                    biblioteca[totallivros].autor[strcspn(biblioteca[totallivros].autor, "\n")] = '\0';
                    biblioteca[totallivros].editora[strcspn(biblioteca[totallivros].editora, "\n")] = '\0';

                    printf("Digite a edição: ");
                    scanf("%d", &biblioteca[totallivros].edicao);
                    LimparBufferDeEntrada();

                    //TORNAR LIVRO DISPONÍVEL AO CADASTRAR
                    biblioteca[totallivros].disponivel = 1;


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
                        printf("Livro %d\n", i + 1);
                        printf("Nome %s\n", biblioteca[i].nome);
                        printf("Autor %s\n", biblioteca[i].autor);
                        printf("Editora %s\n", biblioteca[i].editora);
                        printf("Edição: %d\n", biblioteca[i].edicao);
                    }
                    printf(" ------------------------------ \n");
                }
                
                printf("Pra continuar, pressione Enter: ");
                getchar();
                break;
            
            case 3: //REALIZANDO O EMPRÉSTIMO
                printf(" --- Realizar Empréstimo ---\n\n");

                if (totalemprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de empréstimos atingido!\n");
                } else {
                    printf("Livros disponíveis:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totallivros; i++) {
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("Nenhum livro disponível para empréstimo :/ \n");
                    } else {
                        printf("\nDigite o número do livro que deseja emprestar: ");
                        int numLivro;
                        scanf("%d", &numLivro);
                        LimparBufferDeEntrada();

                        int indice = numLivro - 1; //CONVERTE PARA O INDICE DO ARRAY (0 A N-1).

                        //Validação de escolha do usuário
                        if (indice >= 0 && indice < totallivros && biblioteca[indice].disponivel) {
                            printf("Digite o nome do usuário que está pegando o livro: ");
                            fgets(emprestimos[totalemprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalemprestimos].nomeUsuario[strcspn(emprestimos[totalemprestimos].nomeUsuario, "\n")] = '\0';

                            //Registra o empréstimo
                            emprestimos[totalemprestimos].indiceLivro = indice;

                            //Atualiza o status do livro para indisponível.
                            biblioteca[indice].disponivel = 0;

                            totalemprestimos++;
                            printf("\nEmpréstimo realizado com sucesso! \n");

                        } else {
                            printf("\nNúmero de livro inválido ou livro indisponível.\n");
                        }

                    }
                }
                printf("\nPressione Entrer para continuar...");
                getchar();
                break;
            
            case 4: //LISTANDO OS EMPRÉSTIMOS
                printf(" --- Lista de empréstimos ---\n\n");
                if (totalemprestimos == 0) {
                    printf("Nenhum empréstimo realizado.\n");
                } else {
                    for (int i = 0; i< totalemprestimos; i++) {
                        //USA O ÍNDICE ARMAZENADO NO EMPRÉSTIMO PARA BUSCAR O NOME DO LIVRO
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("-----------------------------------\n");
                        printf("EMPRÉSTIMO %d\n", i +1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuário: %s\n", emprestimos[i].nomeUsuario);
                    }
                    printf("-----------------------------------\n");
                }


            case 0: //SAIR
                printf("\nEncerrando por hoje...\n");
                break;

            default: //OPÇÕES INVÁLIDAS
                printf("\nOpção inválida! Pressione Enter e tente novamente \n");
                getchar();
                break;
        }
    } while (opcao != 0);

    // LIBERAÇÃO DA MEMÓRIA
    free(biblioteca);
    free(emprestimos);
    printf("Memória liberada com sucesso!\n");
    
    return 0; //THAT'S ALL FOLKS ...

}