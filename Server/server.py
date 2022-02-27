import zmq
import argparse
import sortingalgs as sa

def sortLineOfInts(line, sorthingAlgorithm = sa.mergeSort):  
    arr = [int(i) for i in line.split()]
    sorthingAlgorithm(arr)   
    sortedLine = " ".join([str(i) for i in arr])
    return sortedLine

def pollSocket(socket, timetick = 100):
    poller = zmq.Poller()
    poller.register(socket, zmq.POLLIN)
    # wait up to 100msec
    try:
        while True:
            obj = dict(poller.poll(timetick))
            if socket in obj and obj[socket] == zmq.POLLIN:
                yield socket.recv()
    except KeyboardInterrupt:
        print("W: interrupt received, killing server...")
    # Escape while loop if there's a keyboard interrupt.

def main(portNumber):       
    try:
        context = zmq.Context()
        socket = context.socket(zmq.REP)
        socket.bind("tcp://*:" + str(portNumber))
        print("Binding to port " + str(portNumber))

        for line in pollSocket(socket):
            print(f"Received request: {line}")
            sortedLine = sortLineOfInts(line) 
            socket.send(sortedLine.encode('utf-8'))
            
    except zmq.ZMQError as error:
        print(error)
    except KeyboardInterrupt:
        print("W: interrupt received, killing server...")   
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description = 'Generates txt file ')
    parser.add_argument('portNumber',  nargs='?', type=int, default=5555, help='port number')
    args = parser.parse_args()
    main(args.portNumber)    