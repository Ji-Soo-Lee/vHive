import os
import logging
import grpc
from concurrent import futures
from multiprocessing import Process

import helloworld_pb2
import helloworld_pb2_grpc

responses = ["record_response", "replay_response"]

def infinite_loop():
    # Bind each process to a different CPU core
    pid = os.getpid()
    os.sched_setaffinity(pid, {pid % os.cpu_count()})
    
    # Perform a no-op computation to ensure it is not optimized away
    while True:
        _ = 1 + 1  # Simple operation to simulate CPU load

# processes = []

# # Use up to 10 cores, or all but 10 if there are more available
# num_processes = max(1, min(10, os.cpu_count() - 10))

# for _ in range(num_processes):
#     p = Process(target=infinite_loop)
#     p.start()
#     processes.append(p)

processes = []
p = Process(target=infinite_loop)
p.start()
processes.append(p)

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    def SayHello(self, request, context):
        if request.name == "record":
            msg = 'Hello, %s!' % responses[0]
        elif request.name == "replay":
            msg = 'Hello, %s!' % responses[1]
        else:
            msg = 'Hello, %s!' % request.name

        return helloworld_pb2.HelloReply(message=msg)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=os.cpu_count()))
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
    logging.basicConfig()
    serve()

    # Join all processes before exiting
    # for p in processes:
    #     p.join()
