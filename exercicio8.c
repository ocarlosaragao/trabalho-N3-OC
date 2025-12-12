#include <stdio.h>
#include <stdlib.h>

int bcd_para_int(int bcd[4]) {
    return bcd[0]*8 + bcd[1]*4 + bcd[2]*2 + bcd[3];
}

void int_para_bin4(int valor, int bin[4]) {
    bin[0] = (valor >> 3) & 1;
    bin[1] = (valor >> 2) & 1;
    bin[2] = (valor >> 1) & 1;
    bin[3] = valor & 1;
}

int subtrai_bcd(int *A, int *B, int *C, int n) {
    int borrow = 0;

    for (int i = n - 1; i >= 0; i--) {
        int a[4], b[4];

        for (int j = 0; j < 4; j++) {
            a[j] = A[4*i + j];
            b[j] = B[4*i + j];
        }

        int va = bcd_para_int(a);
        int vb = bcd_para_int(b);

        if (va < vb + borrow) {
            va += 10;
            va -= (vb + borrow);
            borrow = 1;
        } else {
            va -= (vb + borrow);
            borrow = 0;
        }

        int res[4];
        int_para_bin4(va, res);

        for (int j = 0; j < 4; j++) {
            C[4*i + j] = res[j];
        }
    }

    return borrow == 0;
}

void imprime_binario(int *v, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("%d", v[i]);
        if ((i + 1) % 4 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    int n = 3;
    int A[12] = {
        0,0,0,1,  
        0,0,1,0,   
        0,0,1,1    
    };

    int B[12] = {
        0,0,0,0,   
        0,0,0,1,   
        0,0,1,1    
    };

    int C[12];

    if (!subtrai_bcd(A, B, C, n)) {
        printf("Erro: subtracao impossivel (A < B)\n");
        return 1;
    }

    printf("Resultado (BCD em binario):\n");
    imprime_binario(C, 12);

    return 0;
}
