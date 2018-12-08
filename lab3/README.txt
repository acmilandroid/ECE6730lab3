/***************
 * Basil Lin
 * ECE 6730
 * README.txt
 ***************/
 
To compile serial programs:
gcc make-matrix.c -o make-matrix
gcc print-matrix.c -o print-matrix
gcc mv-serial.c -o mv-serial

To compile parallel program:
gcc mv-parallel.c -o mv-parallel -fopenmp

Example run:
./make-matrix -n 1000 -l 0 -u 100 -m -o matrix.bin
./make-matrix -n 1000 -l 0 -u 100 -v -o vector.bin
./mv-serial matrix.bin vector.bin serial.bin
./print-matrix serial.bin
qsub openmp.pbs
./print-matrix parallel.bin
diff serial.bin parallel.bin

Notes:
- openmp.pbs requires matrix.bin, vector.bin, and
  outputs to parallel.bin
- serial.bin and parallel.bin will match when using diff
