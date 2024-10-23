    #include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

// matrix multipication 

struct matrixpair {
    int** mat1;
    int** mat2;
    int** ans;
    // int m;
    int n;
    int i;
    int j;
};

void* multiply(void* d) {
    struct matrixpair* p = (struct matrixpair*)d;
    int sum = 0;
    for (int k = 0; k < p->n; k++) {
        sum += p->mat1[p->i][k] * p->mat2[k][p->j];
    }
    p->ans[p->i][p->j] = sum;
    return NULL;
}

int main() {
    int arr1[4][5] = {{1, 1, 1, 1, 1},{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}};
    int arr2[5][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    
    // int arr1[4][5] = {{1, 1, 1, 1, 1}, {2, 2, 2, 2, 2}, {3, 3, 3, 3, 3}, {4, 4, 4, 4, 4}};
    // int arr2[5][4] = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
    int ans[4][4] = {0};

    // Convert the arrays into pointers for easy manipulation
    int* ptr_arr1[4];
    int* ptr_arr2[5];
    int* ptr_ans[4];
    for (int i = 0; i < 4; i++) {
        ptr_arr1[i] = arr1[i];
        ptr_ans[i] = ans[i];
    }
    for (int i = 0; i < 5; i++) {
        ptr_arr2[i] = arr2[i];
    }

    pthread_t threads[4][4];

    // Create threads for matrix multiplication
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            struct matrixpair* m = (struct matrixpair*)malloc(sizeof(struct matrixpair));
            m->mat1 = ptr_arr1;
            m->mat2 = ptr_arr2;
            m->ans = ptr_ans;
            // m->m = 4;
            m->n = 5;
            m->i = i;
            m->j = j;
            pthread_create(&threads[i][j], NULL, multiply, (void*)m);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Print the result matrix
    printf("Resultant Matrix:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}
