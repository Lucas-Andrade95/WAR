#include <stdio.h>
#include <stdlib.h>

int main() {
    float *nota_do_aluno; //Ponteiro para o vetor
    int qtd;
    float soma =0, media = 0;

    printf("Quantidade de alunos: "); // Verificando quantos alunos temos na classe
    scanf("%d", &qtd);
    if (qtd <= 0) {
        printf("A quantidade de alunos deve ser maior que zero.");
        return 1;
    }

    //ALOCANDO MEMÓRIA DINAMICAMENTE PARA A QTD DE ALUNOS INFORMADA
    nota_do_aluno = (float *) calloc(qtd, sizeof(float));

    //VERIFICANDO SE A ALOCAÇÃO FUNCIONOU
    if (nota_do_aluno ==NULL) {
        printf("Falha na alocação de memória \n");
        return 1;
    }

    //Lendo as notas dos alunos e somando
    for (int i = 0; i < qtd; i++) {
        printf("\nNota do aluno %d --> ", i + 1);
        scanf("%f", nota_do_aluno + i);
        soma += nota_do_aluno[i];
    }

    media = soma / qtd;
    printf("\nA média de notas da classe é %.2f \n", media);

    //LIBERANDO ESPAÇO DA MEMÓRIA
    free(nota_do_aluno);
    return 0;
    
    }

    

