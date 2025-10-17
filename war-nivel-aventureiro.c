#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//constantes globais
#define TAM_NOME 30
#define TAM_COR 10

//definição da struct
struct Territorio {
    char nome [30];
    char cor [10];
    int tropas;
};

//CABEÇALHO
void inicio() {
    printf(" ----------------------------------- \n");
    printf(" --------------- WAR --------------- \n");
    printf(" ----------------------------------- \n\n");
}

// função para limpar o buffer de entrada
void LimparBufferDeEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//FUNÇÃO PARA CRIAR MUNDOS
struct Territorio *criaMundo(int *total) {
    printf("Digite a quantidade de territórios do jogo (mín. 2): ");
    scanf("%d", total);
    if (*total < 2) {
        printf("O número de territórios deve ser 2 ou mais.");
        return NULL;
    }
    LimparBufferDeEntrada();
    
    //Alocando dinamicamente
    struct Territorio *mundo = calloc(*total, sizeof(struct Territorio));

    //Verificando se a alocação deu certo
    if (mundo == NULL) {
        printf("Falha na alocação de memória.");
    }

    return mundo;

};

//FUNÇÃO PARA CADASTRAR TERRITORIOS
void cadastrarTerritorios(struct Territorio *mundo, int total) {
        printf("==========================================================\n");
    printf("\nVamos cadastrar os %d territórios iniciais do nosso mundo.\n", total);

    //LOOP for para criar os territórios
    for ( int i = 0; i < total; i++) {

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

    printf("\nCadastro inicial concluído com sucesso!\n");
    return;
}

//FUNÇÃO PARA EXIBIR O MAPA
void exibirMapa(const struct Territorio *mundo, int total) {
    printf("\n==========================================\n");
    printf("\n     MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("\n==========================================\n");

    //LOOP para Exibir os territórios
    for (int i = 0; i < total; i++) {
        printf("\nTERRITÓRIO %d:\n", i + 1);
        printf(" - Nome: %s\n", mundo[i].nome);
        printf(" - Dominado por: Exército %s\n", mundo[i].cor);
        printf(" - Tropas: %d\n\n", mundo[i].tropas);
    }
    return;
}

int verificarVencedor(struct Territorio *mundo, int total) {
    char corReferencia[TAM_COR];
    strcpy(corReferencia, mundo[0].cor);
    for (int i = 1; i < total; i++) {
        if (strcmp(mundo[i].cor, corReferencia) != 0) {
        return 0; // ainda não há vencedor, cores diferentes
        }
    }
    return 1; //Fim de jogo
}

//FUNÇÃO DE ATAQUE E ATUALIZAÇÃO DO MAPA
int atacar(struct Territorio *mundo, int total) {
    exibirMapa(mundo, total);
    int iAtacante, iDefensor;
    printf("\n====================================\n");
    printf("          FASE DE ATAQUE            \n");
    printf("====================================\n");
    printf("Escolha o território atacante (ou 0 para sair): "); 
    scanf("%d", &iAtacante);
    if (iAtacante == 0){
        printf("Saindo da fase de ataque... ");
        return 1;
    }
    printf("Escolha o território defensor: ");
    scanf("%d", &iDefensor);

    //LIMPANDO BUFFER DE ENTRADA
    LimparBufferDeEntrada();

    //VALIDAÇÕES DA ENTRADA
    if (iAtacante < 1 || iAtacante > total || iDefensor < 1 || iDefensor > total || iAtacante == iDefensor) {
    printf("Escolha inválida. Tente novamente.\n");
    return 0;
    }

    //ATRIBUINDO OS NUMEROS DIGITADOS AOS TERRITORIOS
    struct Territorio *atacante = &mundo[iAtacante - 1];
    struct Territorio *defensor = &mundo[iDefensor - 1];

    //VALIDANDO SE OS DOIS TERRITÓRIOS SÃO DE EXÉRCITOS DIFERENTES
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Os dois territórios estão sob domínio do mesmo exército. Escolha novamente.\n");
        return 0;  // reinicia a fase de ataque
    }
    
    //ROLANDO OS DADOS E MOSTRANDO OS RESULTADOS
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
 
    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou %d.\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou %d.\n", defensor->nome, dadoDefensor);

    //LÓGICA DA BATALHA E ATUALIZAÇÃO DOS DADOS
    if (dadoAtacante > dadoDefensor) {
        defensor->tropas--;
        printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa\n");
        if (defensor->tropas <= 0) {
            printf("CONQUISTA! O território %s foi conquistado pelo exército %s.\n", defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;  // novo dono começa com 1 tropa
        }
    } else {
        atacante->tropas--;
        printf("VITÓRIA DA DEFESA! O atacante perdeu 1 tropa\n");
        if (atacante->tropas <= 0) {
            printf("CONQUISTA! O território %s foi conquistado pelo exército %s.\n", atacante->nome, defensor->cor);
            strcpy(atacante->cor, defensor->cor);
            atacante->tropas = 1;  // novo dono começa com 1 tropa
        }
    }

    printf("\nPressione Enter para contninuar... ");
    LimparBufferDeEntrada();

    return 0;
}

//FUNÇÃO PARA LIBERAR MEMÓRIA ALOCADA DINAMICAMENTE
void liberarMundo(struct Territorio *mundo) {
    free(mundo);
    return;
}

//FUNÇÃO PRINCIPAL 
int main() {
    srand(time(NULL));

    //Criando um vetor para o jogo
    struct Territorio *mundo;
    int TotalTerritorios = 0; //variável para armazenar o número de territórios

    //Cabeçalho do jogo
    inicio();

    //CRIANDO TERRITÓRIOS E ALOCANDO MEMÓRIA DINAMICAMENTE
    mundo = criaMundo(&TotalTerritorios);
    if (mundo == NULL) {
        return 1;
    }

    //Chamando a função de Cadastro
    cadastrarTerritorios(mundo, TotalTerritorios);

    //Chamando a função da fase de ataque enquanto não houver um vencedor
    int sair = 0;
    do {
        sair = atacar(mundo, TotalTerritorios);
    } while (sair == 0 && verificarVencedor(mundo, TotalTerritorios) == 0);

    if (verificarVencedor(mundo, TotalTerritorios) == 1) {
        exibirMapa(mundo, TotalTerritorios);
        char corReferencia[TAM_COR];
        strcpy(corReferencia, mundo[0].cor);
        printf("\nO Exército %s conquistou todos os territórios e É O VENCEDOR!!!\n\n FIM DE JOGO", corReferencia);

    }

    //LIBERANDO MEMÓRIA
    liberarMundo(mundo);

    return 0; //THAT'S ALL FOLKS ...
}
