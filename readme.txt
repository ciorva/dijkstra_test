The code tests three implementations of dijkstra algorithm on 
Erdos-Reni random graphs. The implementations differs by 
the  priority queue used:

- Binary Heap
- Binomial Heap
- Fibonacci Heap

The execution time of each test can be found in file outputTest.txt

In order to compile the project:

    mkdir compile
    cd compile
    cmake ..
    make
    cd ..


Usage:

   ./bin/dijkstra_exe [#tests [#node in random graphs]]

 
