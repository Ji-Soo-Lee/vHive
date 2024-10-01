#include <stdio.h>
#include <pthread.h>

void* infinite_loop() {
    while (1) {
        // loop
    }
    return NULL;
}

int main() {
    pthread_t threads[20];  // 20 threads (20 cores)
    
    // create thread and put loop
    for (int i = 0; i < 20; i++) {
        pthread_create(&threads[i], NULL, infinite_loop, NULL);
    }

    // wait
    for (int i = 0; i < 20; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}
