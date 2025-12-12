#include <stdio.h>
#include <stdlib.h>

void imprime_bcd(int *v, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d", v[i]);
    }
    printf("\n");
}

int bcd_para_decimal(int *v, int inicio) {
    int valor = 0;
    for (int i = 0; i < 4; i++) {
        valor = valor * 2 + v[inicio + i];
    }
    return valor;
}

void decimal_para_bcd(int valor, int *v, int inicio) {
    for (int i = 3; i >= 0; i--) {
        v[inicio + i] = valor % 2;
        valor /= 2;
    }
}

int main() {
    int n;
    printf("Digite n (quantidade de dígitos BCD): ");
    scanf("%d", &n);

    int tam = 4 * n;

    int *A = malloc(tam * sizeof(int));
    int *B = malloc(tam * sizeof(int));
    int *C = calloc(tam + 4, sizeof(int));

    printf("Digite o numero A em BCD (%d bits):\n", tam);
    for (int i = 0; i < tam; i++) {
        scanf("%d", &A[i]);
    }

    printf("Digite o numero B em BCD (%d bits):\n", tam);
    for (int i = 0; i < tam; i++) {
        scanf("%d", &B[i]);
    }

    int carry = 0;
    int posC = tam + 4 - 4;

    for (int i = tam - 4; i >= 0; i -= 4) {
        int dA = bcd_para_decimal(A, i);
        int dB = bcd_para_decimal(B, i);

        int soma = dA + dB + carry;

        if (soma >= 10) {
            soma -= 10;
            carry = 1;
        } else {
            carry = 0;
        }

        decimal_para_bcd(soma, C, posC);
        posC -= 4;
    }

    if (carry == 1) {
        decimal_para_bcd(1, C, posC);
    }

    printf("\nResultado da soma em BCD:\n");
    imprime_bcd(C, tam + 4);

    free(A);
    free(B);
    free(C);

    return 0;
}
