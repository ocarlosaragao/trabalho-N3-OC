#include <stdio.h>
#include <stdlib.h>


long long binario_para_decimal(int *V, int n) {
    long long valor = 0;

    for (int i = 0; i < n; i++) {
        valor = (valor << 1) | V[i];
    }


    if (V[0] == 1) {
        valor -= (1LL << n);
    }

    return valor;
}


void decimal_para_binario(long long valor, int *C, int bits) {
    unsigned long long temp;

    if (valor < 0) {
        temp = (1ULL << bits) + valor;
    } else {
        temp = valor;
    }

    for (int i = bits - 1; i >= 0; i--) {
        C[i] = temp & 1;
        temp >>= 1;
    }
}

int main() {
    int n;

    printf("Digite o numero de bits n: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));
    int *C = malloc(2 * n * sizeof(int));

    if (!A || !B || !C) {
        printf("Erro de memoria.\n");
        return 1;
    }

    printf("Digite o vetor A (%d bits, MSB -> LSB):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    printf("Digite o vetor B (%d bits, MSB -> LSB):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    long long a = binario_para_decimal(A, n);
    long long b = binario_para_decimal(B, n);

    long long produto = a * b;

    decimal_para_binario(produto, C, 2 * n);

    printf("\nResultado da multiplicacao (2n bits):\n");
    for (int i = 0; i < 2 * n; i++) {
        printf("%d", C[i]);
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}
