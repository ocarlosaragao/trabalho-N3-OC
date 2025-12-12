#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Digite o numero de bits: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada invalida.\n");
        return 1;
    }

    int *A = (int *)malloc(n * sizeof(int));
    int *B = (int *)malloc(n * sizeof(int));
    int *C = (int *)malloc((n + 1) * sizeof(int));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Erro: memoria insuficiente.\n");
        free(A);
        free(B);
        free(C);
        return 1;
    }

    printf("Digite os %d bits de A (0 ou 1), em ordem (MSB -> LSB):\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &A[i]) != 1 || (A[i] != 0 && A[i] != 1)) {
            printf("Bit invalido em A.\n");
            free(A); free(B); free(C);
            return 1;
        }
    }

    printf("Digite os %d bits de B (0 ou 1), em ordem (MSB -> LSB):\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &B[i]) != 1 || (B[i] != 0 && B[i] != 1)) {
            printf("Bit invalido em B.\n");
            free(A); free(B); free(C);
            return 1;
        }
    }

    int carry = 0;

    for (int i = n - 1; i >= 0; i--) {
        int soma = A[i] + B[i] + carry;
        C[i + 1] = soma % 2;
        carry = soma / 2;
    }
    C[0] = carry;

    printf("Resultado (C, com %d bits): ", n + 1);
    for (int i = 0; i < n + 1; i++) {
        printf("%d", C[i]);
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}
