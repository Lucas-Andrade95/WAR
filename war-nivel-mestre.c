#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//definição da struct
struct Territorio {
    char nome [30];
    char cor [10];
    int tropas;
};

//DECLARANDO TERRITORIOS (NÃO É NECESSÁRIO USAR PONTEIRO UMA VEZ QUE SERÃO FIXOS NESSE NÍVEL)
struct Territorio territorios[5] = {
    {"America", "Verde", 0},
    {"Europa", "Azul", 0},
    {"Asia", "Vermelho", 0},
    {"Africa", "Amarelo", 0},
    {"Oceania", "Branco", 0}
    };

//VETOR DE STRINGS COM AS MISSÕES DO JOGO
char *missoes[] = {
    "Conquistar 3 territorios",
    "Destruir o exército Amarelo",
    "Destruir o exército Verde",
    "Destruir o exército Branco",
    "Destruir o exército Vermelho"
};

// função para limpar o buffer de entrada
void LimparBufferDeEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//CABEÇALHO
void inicio() {
    printf(" --------------- WAR --------------- \n");
}

//FUNÇÃO PARA ATRIBUIR TROPAS ALEATORIAMENTE
void atribuirTropas() {

    srand(time(NULL)); // Inicializa o gerador aleatório
    for (int i = 0; i < 5; i++) {
        territorios[i].tropas = rand() % 5 + 1; // gera número entre 1 e 5
    }

}

//FUNÇÃO PARA EXIBIR O MAPA
void exibirMapa() {
    printf("     MAPA DO MUNDO - ESTADO ATUAL    \n");
    printf("==========================================\n");

    //LOOP para Exibir os territórios
    for (int i = 0; i < 5; i++) {
        printf("\nTERRITÓRIO %d:\n", i + 1);
        printf(" - Nome: %s\n", territorios[i].nome);
        printf(" - Dominado por: Exército %s\n", territorios[i].cor);
        printf(" - Tropas: %d\n\n", territorios[i].tropas);
    }
    return;
}

//FUNÇÃO PARA ATRIBUIR MISSÃO ALEATÓRIA
int atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    srand(time(NULL));
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
    printf("\n---- SUA MISSÃO (Exército Azul) ----\n\n%s\n", missoes[sorteio]);
    return sorteio;
}

int verificarMissao(int sorteio) {
    switch (sorteio)
    {
    case 0:
        // percorre o vetor 'territorios' e conta quantos têm cor "Azul"
        int conquistados = 0;
        for (int i = 0; i < 5; i++) {
            if (strcmp(territorios[i].cor, "Azul") == 0)
                conquistados++;
        }   
        if (conquistados >= 3)
        return 1;
        break;   

    case 1:
        int existeAmarelo = 0;
        for (int i = 0; i < 5; i++) {
            if (strcmp(territorios[i].cor, "Amarelo") == 0)
                existeAmarelo = 1;
        }
        if (!existeAmarelo)
        return 1;
        break;

    case 2:
        int existeVerde = 0;
        for (int i = 0; i < 5; i++) {
            if (strcmp(territorios[i].cor, "Verde") == 0)
                existeVerde = 1;
        }
        if (!existeVerde)
        return 1;
        break;

    case 3:
        int existeBranco = 0;
        for (int i = 0; i < 5; i++) {
        if (strcmp(territorios[i].cor, "Branco") == 0)
            existeBranco = 1;
        }
        if (!existeBranco)
        return 1;
        break;

    case 4:
        int existeVermelho = 0;
        for (int i = 0; i < 5; i++) {
        if (strcmp(territorios[i].cor, "Vermelho") == 0)
            existeVermelho = 1;
        }
        if (!existeVermelho)
        return 1;
        break;
    
    default:
        printf("Opção inválida! Tente novamente");
        break;
    }
    return 0;
}

//FUNÇÃO DE ATAQUE E ATUALIZAÇÃO DO MAPA
int atacar() {

    int iAtacante, iDefensor;

    printf("\n====================================\n");
    printf("          FASE DE ATAQUE            \n");
    printf("====================================\n");
    printf("Escolha o território atacante (ou 0 para sair): "); 
    scanf("%d", &iAtacante);

    if (iAtacante == 0){
        printf("Saindo da fase de ataque...\n");
        return 1;
    }

    printf("Escolha o território defensor: ");
    scanf("%d", &iDefensor);
    LimparBufferDeEntrada();

    //VALIDAÇÕES
    if (iAtacante < 1 || iAtacante > 5 || iDefensor < 1 || iDefensor > 5 || iAtacante == iDefensor) {
        printf("Escolha inválida. Tente novamente.\n");
        return 0;
    }

    //REFERÊNCIAS DIRETAS AOS TERRITÓRIOS
    struct Territorio *atacante = &territorios[iAtacante - 1];
    struct Territorio *defensor = &territorios[iDefensor - 1];

    //VALIDANDO CORES
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Os dois territórios estão sob domínio do mesmo exército. Escolha novamente.\n");
        return 0;
    }

    //ROLANDO OS DADOS
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou %d.\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou %d.\n", defensor->nome, dadoDefensor);

    //LÓGICA DA BATALHA
    if (dadoAtacante > dadoDefensor) {
        defensor->tropas--;
        printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        if (defensor->tropas <= 0) {
            printf("CONQUISTA! O território %s foi conquistado pelo exército %s.\n",
                   defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;
        }
    } else {
        atacante->tropas--;
        printf("VITÓRIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        if (atacante->tropas <= 0) {
            printf("CONQUISTA! O território %s foi conquistado pelo exército %s.\n",
                   atacante->nome, defensor->cor);
            strcpy(atacante->cor, defensor->cor);
            atacante->tropas = 1;
        }
    }

    printf("\nPressione Enter para continuar...\n");
    LimparBufferDeEntrada();

    return 0;
}

int Menu() {
    int opcao;
    printf("\n --- MENU --- \n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
    printf("---> ");
    scanf("%d", &opcao);
    LimparBufferDeEntrada();
    return opcao;
}


int main() {
    inicio();
    atribuirTropas();
    exibirMapa();
    int totalMissoes = 5;
    int vitoria = 0;

    // aloca espaço para a missão (máximo de 100 caracteres)
    char *missaoJogador = malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para a missão!\n");
        return 1;
    }

    // Seleciona uma missão aleatoriamente e guarda na variável indiceMissao
    int indiceMissao = atribuirMissao(missaoJogador, missoes, totalMissoes);

    //FAÇA ENQUANTO A MISSÃO NÃO FOR CONCLUÍDA
    do {
    vitoria = verificarMissao(indiceMissao);
    
    int opcao = Menu();
    if (opcao == 1) {
        atacar();
        exibirMapa();
        vitoria = verificarMissao(indiceMissao); //VERIFICA SE A MISSÃO FOI CONCLUÍDA
    } else if (opcao == 2) {
        printf("\nSua missão: %s", missoes[indiceMissao]);
    } else {
        printf("SAINDO...");
        break;
    }

    } while (vitoria == 0);
    
    if (vitoria == 1) {
        printf("PARABÉNS! VOCÊ VENCEU!!!");
    }

    // libera a memória no final
    free(missaoJogador);
}
