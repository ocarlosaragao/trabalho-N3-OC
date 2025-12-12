#include <stdio.h>
#include <stdlib.h>


void imprime_binario(int *v, int n) {
    for (int i = 0; i < n; i++)
        printf("%d", v[i]);
    printf("\n");
}


void copia(int *dest, int *orig, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = orig[i];
}


int maior_ou_igual(int *A, int *B, int n) {
    for (int i = 0; i < n; i++) {
        if (A[i] > B[i]) return 1;
        if (A[i] < B[i]) return 0;
    }
    return 1; 
}


void subtrai(int *A, int *B, int n) {
    int borrow = 0;
    for (int i = n - 1; i >= 0; i--) {
        int diff = A[i] - B[i] - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        A[i] = diff;
    }
}


void shift_left(int *v, int n, int bit) {
    for (int i = 0; i < n - 1; i++)
        v[i] = v[i + 1];
    v[n - 1] = bit;
}


int divide_binario(int *A, int *B, int *C, int *R, int n) {
   
    int zero = 1;
    for (int i = 0; i < n; i++) {
        if (B[i] != 0) {
            zero = 0;
            break;
        }
    }

    if (zero) return 0; 

    
    for (int i = 0; i < n; i++) {
        C[i] = 0;
        R[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        shift_left(R, n, A[i]);

        if (maior_ou_igual(R, B, n)) {
            subtrai(R, B, n);
            C[i] = 1;
        }
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
    int *R = malloc(n * sizeof(int));

    if (!A || !B || !C || !R) {
        printf("Erro de memoria.\n");
        return 1;
    }

    printf("Digite o dividendo (A) em binario (MSB -> LSB):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Digite o divisor (B) em binario (MSB -> LSB):\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &B[i]);

    if (!divide_binario(A, B, C, R, n)) {
        printf("Erro: divisao por zero.\n");
    } else {
        printf("Quociente (C): ");
        imprime_binario(C, n);

        printf("Resto (R): ");
        imprime_binario(R, n);
    }

    free(A);
    free(B);
    free(C);
    free(R);

    return 0;
}
