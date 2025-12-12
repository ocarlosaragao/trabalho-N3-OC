#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


static int le_bit(void) {
    int x;
    if (scanf("%d", &x) != 1) return -1;
    return (x == 0 || x == 1) ? x : -1;
}

static int soma_bits_twos_complement(const int *A, const int *B, int *C, int W) {
    int carry = 0;

    
    for (int i = W - 1; i >= 0; --i) {
        int a = A[i], b = B[i];
        int s = a ^ b ^ carry;
        int c_out = (a & b) | (a & carry) | (b & carry);
        C[i] = s;
        carry = c_out;
    }

    
    int signA = A[0], signB = B[0], signC = C[0];
    if ((signA == signB) && (signC != signA)) return 0;

    return 1;
}

static void imprime_hex(const int *C, int W) {
    
    int n = W / 4;

    for (int k = 0; k < n; ++k) {
        int base = 4 * k;
        int val = (C[base] << 3) | (C[base + 1] << 2) | (C[base + 2] << 1) | (C[base + 3]);

        char ch = (val < 10) ? (char)('0' + val) : (char)('A' + (val - 10));
        putchar(ch);
    }
    putchar('\n');
}

int main(void) {
    int n;
    printf("Digite n (numero de digitos hex; largura = 4n bits): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada invalida.\n");
        return 1;
    }

    int W = 4 * n;

    int *A = (int*)malloc(W * sizeof(int));
    int *B = (int*)malloc(W * sizeof(int));
    int *C = (int*)malloc(W * sizeof(int));
    if (!A || !B || !C) {
        printf("Erro: memoria insuficiente.\n");
        free(A); free(B); free(C);
        return 1;
    }

    printf("Digite os %d bits de A (MSB->LSB), separados por espaco:\n", W);
    for (int i = 0; i < W; ++i) {
        int bit = le_bit();
        if (bit < 0) {
            printf("Bit invalido em A.\n");
            free(A); free(B); free(C);
            return 1;
        }
        A[i] = bit;
    }

    printf("Digite os %d bits de B (MSB->LSB), separados por espaco:\n", W);
    for (int i = 0; i < W; ++i) {
        int bit = le_bit();
        if (bit < 0) {
            printf("Bit invalido em B.\n");
            free(A); free(B); free(C);
            return 1;
        }
        B[i] = bit;
    }

    if (!soma_bits_twos_complement(A, B, C, W)) {
        printf("ERRO: overflow (soma nao cabe em %d bits com sinal).\n", W);
        free(A); free(B); free(C);
        return 1;
    }

    printf("Resultado (hex, %d digitos): ", n);
    imprime_hex(C, W);

    free(A); free(B); free(C);
    return 0;
}
