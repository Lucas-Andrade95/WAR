#include <stdio.h>
#include <stdlib.h>

int main() {
    //DECLARANDO VARIÁVEIS
    float *nota_do_aluno; //Ponteiro vetor float
    int qtd;
    float maior_nota = 0, menor_nota = 0, soma = 0, media = 0;

    //VERIFICA QUANTOS ALUNOS TEM

    printf("Quantidade de alunos: ");
    scanf("%d", &qtd);

    //ALOCAR DINAMICAMENTE MEMÓRIA PARA O VETOR nota_do_aluno
    nota_do_aluno = (float *) malloc(qtd * sizeof(float));

    //VERIFICANDO SE A MEMÓRIA FOI ALOCADA CORRETAMENTE
    if (nota_do_aluno == NULL) {
        printf("Falha na alocação de memória");
        return 1;
    }

    //LENDO, SOMANDO E CLASSIFICANDO AS NOTAS
    for (int i = 0; i < qtd; i++) {
        printf("\nNota do aluno %d --> ", i +1);
        scanf("%f", nota_do_aluno + i);
        soma += nota_do_aluno[i];
        if (i == 0) {
            maior_nota = nota_do_aluno[i];
            menor_nota = nota_do_aluno[i];
        } else {
            if (nota_do_aluno[i] > maior_nota) {
                maior_nota = nota_do_aluno[i];
            };
            if (nota_do_aluno[i] < menor_nota) {
                menor_nota = nota_do_aluno[i];
            };
        };
    }

    media = soma / qtd;

    //MOSTRANDO OS RESULTADOS
    printf("\nA nota máxima da classe é: %.2f\n", maior_nota);
    printf("A nota mínima é: %.2f\n", menor_nota);
    printf("A média da  turma é: %.2f", media);


    //LIBERANDO A MEMÓRIA E ENCERRANDO
    free(nota_do_aluno);
    return 0;
}
