/* Copyright 2016 (Jackie) Xiangqing Zhang & Fred Zhang */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int *array;

void fib(int n) {
    printf("Calling %d\n", n);
    array[0] = 0;
    if (n == 1) {
        return;
    array[1] = 1;
    }
    int i = 2;
    for (i = 2; i < n; i++) {
        array[i] = array[i - 1] + array[i - 2];
    }
    printf("Finishing %d\n", n);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s\n", "Please provide one argument -- number of fib");
        exit(-1);
    }
    int num = atoi(argv[1]);
    if (num <= 0) {
        fprintf(stderr, "%s\n", "Please enter a positive number");
        exit(-2);
    }

    array = ((int *)malloc(num * sizeof(int)));

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, fib, num);
    pthread_join(tid, NULL);
    int i;
    for (i = 0; i < num; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}

