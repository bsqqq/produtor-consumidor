#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t slots_preenchidos;
sem_t slots_vagos;
pthread_mutex_t m;
int in = 0;

void* produtor(void* x) {
    int* ptr = (int*)x;
    int n = *ptr;

    int item = rand();
    sem_wait(&slots_vagos);
    ptherad_mutex_lock(&m);

    //Regiao critica

    buffer[in] = item;
    in = (in + i) % 10;

    ptherad_mutex_unlock(&m);
    sem_post(slots_preenchidos);
    return NULL;
}

int buffer[10];

int main()
{
    pthread_t p1, p2, p3, p4, p5;
    pthread_t c1, c2, c3, c4, c5;

    int np1 = 1, np2 = 2, np3 = 3, np4 = 4, np5 = 5;
    int nc1 = 1, nc2 = 2, nc3 = 3, nc4 = 4, nc5 = 5;

    sem_init(&slots_preenchidos, 0, 0);
    sem_init(&slots_vagos, 0, 0);
    pthread_mutex_unlock(&m);

    pthread_create(&p1, NULL, produtor, &np1);
    pthread_create(&p2, NULL, produtor, &np2);
    pthread_create(&p3, NULL, produtor, &np3);
    pthread_create(&p4, NULL, produtor, &np4);
    pthread_create(&p5, NULL, produtor, &np5);

    pthread_create(&c1, NULL, consumidor, &nc1);
    pthread_create(&c2, NULL, consumidor, &nc2);
    pthread_create(&c3, NULL, consumidor, &nc3);
    pthread_create(&c4, NULL, consumidor, &nc4);
    pthread_create(&c5, NULL, consumidor, &nc5);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);

    pthread_join(c1, NULL);
    pthread_join(c2, NULL);
    pthread_join(c3, NULL);
    pthread_join(c4, NULL);
    pthread_join(c5, NULL);
    printf("Hello world!\n");
    return 0;
}
