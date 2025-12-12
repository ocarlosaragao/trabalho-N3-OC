#include <stdio.h>
#include <stdlib.h>

static int read_bits(int *v, int m) {
    
    int count = 0;
    while (count < m) {
        int ch = getchar();
        if (ch == EOF) return 0;
        if (ch == '0' || ch == '1') {
            v[count++] = (ch - '0');
        }
    }
    return 1;
}

static int add_bits_tc(const int *A, const int *B, int *C, int m) {
    
    int carry = 0;

    
    for (int i = m - 1; i >= 0; --i) {
        int s = A[i] ^ B[i] ^ carry;
        int c_out = (A[i] & B[i]) | (A[i] & carry) | (B[i] & carry);
        C[i] = s;
        carry = c_out;
    }

    
    int signA = A[0];
    int signB = B[0];
    int signC = C[0];
    return (signA == signB) && (signC != signA);
}

static void twos_complement(const int *B, int *Bneg, int m) {
    
    for (int i = 0; i < m; ++i) Bneg[i] = 1 - B[i];

    
    int carry = 1;
    for (int i = m - 1; i >= 0; --i) {
        int s = Bneg[i] ^ carry;
        int c_out = Bneg[i] & carry;
        Bneg[i] = s;
        carry = c_out;
    }
}

static void print_hex_from_bits(const int *C, int m) {
    
    const char *hex = "0123456789ABCDEF";
    for (int i = 0; i < m; i += 4) {
        int val = (C[i] << 3) | (C[i + 1] << 2) | (C[i + 2] << 1) | (C[i + 3]);
        putchar(hex[val]);
    }
    putchar('\n');
}

int main(void) {
    int n;
    printf("Digite n (numero de digitos hex): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: n invalido.\n");
        return 1;
    }

    int m = 4 * n; 

    int *A = (int*)malloc(m * sizeof(int));
    int *B = (int*)malloc(m * sizeof(int));
    int *C = (int*)malloc(m * sizeof(int));
    int *Bneg = (int*)malloc(m * sizeof(int));

    if (!A || !B || !C || !Bneg) {
        printf("Erro: memoria insuficiente.\n");
        free(A); free(B); free(C); free(Bneg);
        return 1;
    }

    printf("Digite A em %d bits (MSB->LSB), ex: 0101...:\n", m);
    
    getchar();
    if (!read_bits(A, m)) {
        printf("Erro ao ler A.\n");
        free(A); free(B); free(C); free(Bneg);
        return 1;
    }

    printf("Digite B em %d bits (MSB->LSB), ex: 0101...:\n", m);
    if (!read_bits(B, m)) {
        printf("Erro ao ler B.\n");
        free(A); free(B); free(C); free(Bneg);
        return 1;
    }

    
    twos_complement(B, Bneg, m);

    
    int overflow_add = add_bits_tc(A, Bneg, C, m);

    
    int signA = A[0], signB = B[0], signC = C[0];
    int overflow_sub = (signA != signB) && (signC != signA);

    if (overflow_add || overflow_sub) {
        printf("ERRO: overflow (resultado nao cabe em %d bits com sinal).\n", m);
        free(A); free(B); free(C); free(Bneg);
        return 1;
    }

    printf("Resultado (binario %d bits): ", m);
    for (int i = 0; i < m; ++i) putchar(C[i] ? '1' : '0');
    putchar('\n');

    printf("Resultado (hex, %d digitos): ", n);
    print_hex_from_bits(C, m);

    free(A); 
    free(B); 
    free(C); 
    free(Bneg);
    
    return 0;
}
