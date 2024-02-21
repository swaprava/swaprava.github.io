#include <stdio.h>
#include <stdlib.h>

int badSatSolver(int* partial, int depth, int size, int** constraints, int numConstraints);
int constraintCheck(int* partial, int a, int b, int c);

int main () {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    
    int **constraints = (int**)calloc(m, sizeof(int*));
    for (int i = 0; i < m; i++) {
        constraints[i] = (int*)calloc(3, sizeof(int));
    }
    int a, b, c;
    for (int j = 0; j < m; j++) {
        scanf("%d %d %d", &a, &b, &c);
        constraints[j][0] = a;
        constraints[j][1] = b;
        constraints[j][2] = c;
    }
    int* partial = (int*)calloc(n, sizeof(int));
    int soln = badSatSolver(partial, 0, n, constraints, m);
    printf("%d", soln);
    return 0;
}

int constraintCheck(int* partial, int a, int b, int c) {
    if (((a > 0) && (partial[a-1] == 1)) || ((a < 0) && (partial[(-a)-1] == -1))) {
        return 1;
    }
    if (((b > 0) && (partial[b-1] == 1)) || ((b < 0) && (partial[(-b)-1] == -1))) {
        return 1;
    }
    if (((c > 0) && (partial[c-1] == 1)) || ((c < 0) && (partial[(-c)-1] == -1))) {
        return 1;
    }
    return 0;
}

int badSatSolver(int* partial, int depth, int size, int** constraints, int numConstraints) {
    if (depth == size) {
        // Base case, have to check other constraints
        if (numConstraints == size - 2) {
            /* Nothing else to check
            for (int j = 0; j < size; j++) {
                partial[j] > 0 ? printf("1") : printf("0");
            }
            printf("\n");
            */
            return 1;
        } else {
            int temp = 1;
            int a, b, c;
            for (int i = size-2; i < numConstraints; i++) {
                a = constraints[i][0];
                b = constraints[i][1];
                c = constraints[i][2];
                temp *= constraintCheck(partial, a, b, c);
            }
            if (temp) {
                /* All good
                for (int j = 0; j < size; j++) {
                    partial[j] > 0 ? printf("1") : printf("0");
                }
                printf("\n");
                */
                return 1;
            } else {
                return 0;
            }
        }
    }
    int soln = 0;
    if (depth < 2) {
        partial[depth] = -1;
        soln += badSatSolver(partial, depth + 1, size, constraints, numConstraints);
        partial[depth] = 1;
        soln += badSatSolver(partial, depth + 1, size, constraints, numConstraints);
    } else {
        int a, b, c;
        a = constraints[depth - 2][0];
        b = constraints[depth - 2][1];
        c = constraints[depth - 2][2];
        partial[depth] = -1;
        if (constraintCheck(partial, a, b, c)) {
            soln += badSatSolver(partial, depth + 1, size, constraints, numConstraints);
        }
        partial[depth] = 1;
        if (constraintCheck(partial, a, b, c)) {
            soln += badSatSolver(partial, depth + 1, size, constraints, numConstraints);
        }
    }
    partial[depth] = 0;
    return soln;
}
