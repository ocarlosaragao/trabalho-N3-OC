#include <stdio.h>
#include <stdlib.h>


int maior_ou_igual(int *A, int *B, int n) {
    for (int i = 0; i < n; i++) {
        if (A[i] > B[i]) return 1;
        if (A[i] < B[i]) return 0;
    }
    return 1;
}

int main() {
    int n;
    printf("Digite o numero de bits: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));
    int *C = malloc(n * sizeof(int));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    printf("Digite o numero binario A (%d bits), em ordem (MSB -> LSB):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    printf("Digite o numero binario B (%d bits), em ordem (MSB -> LSB):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }


    if (!maior_ou_igual(A, B, n)) {
        printf("Erro: subtracao impossivel (B > A).\n");
        free(A);
        free(B);
        free(C);
        return 1;
    }

    int borrow = 0;

    for (int i = n - 1; i >= 0; i--) {
        int diff = A[i] - B[i] - borrow;

        if (diff == -1) {
            C[i] = 1;
            borrow = 1;
        } else if (diff == -2) {
            C[i] = 0;
            borrow = 1;
        } else {
            C[i] = diff;
            borrow = 0;
        }
    }

    printf("Resultado da subtracao (A - B): ");
    for (int i = 0; i < n; i++) {
        printf("%d", C[i]);
    }
    printf("\n");

    free(A);
    free(B);
    free(C);

    return 0;
}
