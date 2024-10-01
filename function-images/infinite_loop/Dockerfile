# Use an official Alpine image
FROM alpine:latest as var_workload

# Install necessary packages (GCC, musl for standard C library, and pthreads)
RUN apk update && \
    apk add --no-cache gcc g++ musl-dev

# Copy the C source file into the root directory of the container
COPY infinite_loop.c /

# Compile the C program with pthread support
RUN gcc -o /infinite_loop /infinite_loop.c -lpthread

# Define the stop signal as SIGKILL
STOPSIGNAL SIGKILL

# Command to run the compiled program
CMD ["/infinite_loop"]
