#include <stdio.h>

int main() {
    int x = 10;
    int* p = &x; //O ponteiro p do tipo inteiro recebe o endereço de x

    printf("Valor de x: %d\n", x);
    printf("Endereço de x: %p\n", &x);
    printf("Conteúdo de p (endereço): %p\n", p);
    printf("Valor apontado por p: %d\n", *p);

    *p = 20; // == int x = 20;

    printf("Valor de x: %d\n", x);
    printf("Endereço de x: %p\n", &x);
    printf("Conteúdo de p (endereço): %p\n", p);
    printf("Valor apontado por p: %d\n", *p);

    return 0;
}