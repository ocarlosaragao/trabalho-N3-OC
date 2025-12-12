#include <stdio.h>
#include <stdlib.h>


int soma_binaria_com_sinal(int *A, int *B, int *C, int n) {
    int carry = 0;

   
    for (int i = n - 1; i >= 0; i--) {
        int soma = A[i] + B[i] + carry;
        C[i] = soma % 2;
        carry = soma / 2;
    }

    
    if (A[0] == B[0] && C[0] != A[0]) {
        return 0; 
    }

    return 1; 
}


void imprime_binario(int *V, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", V[i]);
    }
    printf("\n");
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

    printf("Digite o vetor A (%d bits, MSB -> LSB):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    printf("Digite o vetor B (%d bits, MSB -> LSB):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    if (soma_binaria_com_sinal(A, B, C, n)) {
        printf("Resultado da soma:\n");
        imprime_binario(C, n);
    } else {
        printf("Erro: overflow (resultado nao pode ser representado com %d bits).\n", n);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
