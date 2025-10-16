//PRATICANDO ALOCAÇÃO DINÂMICA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int *numeros; //ponteiro para o vetor
    int qtd, soma = 0;

    //VERIFICANDO QUANTOS NÚMEROS O USUÁRIO QUER SOMAR
    printf("Quantos números deseja somar? --> ");
    scanf("%d", &qtd);

    numeros = (int *) calloc(qtd, sizeof(int)); // Aloca dinamicamente X espaços de memória do tamanho int e guarda o endereço desse vetor na variável números

    // Verificar se a alocação deu certo
    if (numeros == NULL) {
        printf("Falha ao alocar memória\n");
        return 1;
    } else {
        printf("Alocação de memória bem sucedida!\n");
    }

    //LOOP para ler os valores
    for (int i = 0; i < qtd; i++) {
    printf("Digite o número %d: ", i + 1);
    scanf("%d", &numeros[i]);
    soma += numeros[i];
    }

    //mostrar resultado
    printf("\nA soma dos números é: %d\n", soma);

    free(numeros);
    return 0;

}




