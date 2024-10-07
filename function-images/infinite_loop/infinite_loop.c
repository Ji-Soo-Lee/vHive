#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void* infinite_loop() {
    while (1) {
        // loop
    }
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }
    
    // Define the server address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(50051);

    // Bind the socket to the port 50051
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }

    // Accept incoming connections in a loop
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            return -1;
        }
        // Handle accepted connection (if necessary)
    }


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
