## Info

* Original Link: http://www.cse.psu.edu/~kxm85/software/GTgraph/ 
* By default, the makefile random number generator project [sprng2.0-lite](sprng2.0-lite) is compiled with `gcc`, see [Makefile.var](Makefile.var)
* In this work, we support cmake-build system and add support to get binary edge list as outputs, see the later Usages. 
* For the detailed explanation of the generators, check the [Prof. David A. Bader's document](gen.pdf)

## Build

```
mkdir build & cd build
cmake ..
make -j
```

## Cmake-Build

* we build `set(SPRNG_LIB ${CMAKE_CURRENT_SOURCE_DIR}/sprng2.0-lite/lib/libsprng.a)` first, 
and then the other three executables
* `add_custom_command`, `add_custom_target`, `add_dependencies` are used to integrate the existing makefile project for the 
`sprng2.0-lite/lib/libsprng.a` 

## Usage 

see [old_readme.md](old_readme.md)

### SSCA2

* example, scale factor: `10`, output-file-path: `./ssca-s10.bin`

```zsh
 ./GTgraph-ssca2-bin -s 10 -o ssca-s10.bin
```

```
-s ###  SCALE value (integer) to use (default -- 20)
-c ###  config file to use
-o ###  output file to write the graph to (default -- sample.gr)
-h      display this message
```

### Random

* ER-example

```
./GTgraph-random-bin -t 0 -n 10000 -p 0.001 -o er.bin 
```

* Another-Random-example

```
./GTgraph-random-bin -t 1 -n 10000 -m 100000 -o rand2.bin 
```

```
GTgraph-random [-options]
-c ### config file to use
-t ### Specify random graph model to use (0 for Erdos-Renyi G(n, p), 1 for G(n, m), default 1)
-n ### -p ### parameters for Erdos-Renyi (default -- n:10^7, p:10^-6)
-n ### -m ### parameters for G(n, m) (default -- n:10^7, m:10^8)
-o ### output file to write the graph to
-h
display this message
```

> 1. an Erdős-Rényi graph generator which takes as input arguments the number of vertices,
  and the constant probability of an edge between any pair of vertices in the graph.
>  2. a random graph generator which takes as input the number of vertices (n) and edges
  (m), and adds m edges randomly choosing a pair of vertices each time. There is a
  possibility of adding multiple edges between a pair of vertices in this case.

### RMAT

* example, vertex and edge numbers and output-path (`100000`, `100000`, `rmat.bin `)

```
./GTgraph-rmat-bin -n 100000 -m 100000 -o rmat.bin  
```

```
-c  ###	 config file to use
-n  ###  no. of vertices (default -- 10^7)
-m  ###	 no. of edges (default -- 10^8)
-o  ###  output file to write the graph to
-h       display this message
```

## References

* D. Chakrabarti, Y. Zhan and C. Faloutsos, R-MAT: A Recursive Model for Graph Mining, Proc. SIAM Intl. Conf. on Data Mining, 2004

