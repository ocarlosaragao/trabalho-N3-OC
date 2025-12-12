#include <stdio.h>
#include <stdlib.h>


void complemento1(int *B, int *C, int n) {
    for (int i = 0; i < n; i++)
        C[i] = !B[i];
}


int soma_binaria(int *A, int *B, int *C, int n) {
    int carry = 0;

    for (int i = n - 1; i >= 0; i--) {
        C[i] = A[i] ^ B[i] ^ carry;
        carry = (A[i] & B[i]) | (A[i] & carry) | (B[i] & carry);
    }
    return carry;
}


int subtrai_binario(int *A, int *B, int *C, int n) {
    int *negB = malloc(n * sizeof(int));
    int *temp = malloc(n * sizeof(int));

    if (!negB || !temp)
        return 0;

    
    complemento1(B, negB, n);


    int um[1] = {1};
    int carry = 1;
    for (int i = n - 1; i >= 0; i--) {
        int soma = negB[i] + carry;
        negB[i] = soma % 2;
        carry = soma / 2;
    }

   
    soma_binaria(A, negB, C, n);

    
    if (A[0] == negB[0] && C[0] != A[0]) {
        free(negB);
        free(temp);
        return 0;  // erro
    }

    free(negB);
    free(temp);
    return 1;
}

int main() {
    int n;
    printf("Digite o numero de bits: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));
    int *B = malloc(n * sizeof(int));
    int *C = malloc(n * sizeof(int));

    printf("Digite A (MSB -> LSB):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Digite B (MSB -> LSB):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &B[i]);

    if (!subtrai_binario(A, B, C, n)) {
        printf("Erro: overflow na subtracao.\n");
    } else {
        printf("Resultado A - B:\n");
        for (int i = 0; i < n; i++)
            printf("%d", C[i]);
        printf("\n");
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
