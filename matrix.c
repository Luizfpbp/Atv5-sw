#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int totalSoma = 0;

int tamanho;
int linha;
int **matrix; 

void *somaLinha (void *arg);

int main (void) {

    scanf ("%d", &tamanho);

    matrix = (int**) malloc(tamanho*sizeof(int*));
    for (int i=0; i<tamanho; i++) {
        matrix[i] = (int*) malloc(tamanho*sizeof(int));
    }

    for (int m1=0; m1<tamanho; m1++) {
        for (int m2=0; m2<tamanho; m2++) {

            scanf (" %d", &matrix[m1][m2]);

        }
    }

    pthread_t threads[tamanho];

    for (int i=0; i<tamanho; i++) {
        if (pthread_create (&(threads[i]), NULL, somaLinha, NULL)) {
            printf("Thread %d não criada", i);
        }
    }

    for (int i=0; i<tamanho; i++) {
        
        pthread_join(threads[i], NULL);
    }

    printf("%d\n", totalSoma);

    return 0;
}

void *somaLinha (void *arg) {

    pthread_mutex_lock(&mutex);
    
    int soma = 0;
    for (int i=0; i<tamanho; i++) {
        soma += matrix[linha][i];
    }

    totalSoma += soma;
    linha++;

    pthread_mutex_unlock(&mutex);
    return arg;

}
