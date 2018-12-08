/*************************
 * Basil Lin
 * ECE 6730
 * make-matrix.c
 *************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


int main(int argc, char **argv) {

    int i, n, l, u, o, v = 0;
    double randnum;
    
    srand(time(NULL));

    // finds flags and flag argument index
    for (i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) n = i+1;
        if (strcmp(argv[i], "-l") == 0) l = i+1;
        if (strcmp(argv[i], "-u") == 0) u = i+1;
        if (strcmp(argv[i], "-o") == 0) o = i+1;
        if (strcmp(argv[i], "-v") == 0) v = 1;
    }

    int size = atoi(argv[n]);
    int lower = atoi(argv[l]);
    int upper = atoi(argv[u]);

    FILE *out;
    if ((out = fopen(argv[o], "wb")) == NULL) {
		printf("Unable to open %s for writing\n", argv[o]);
		exit(0);
	}

	//writes dimensions
    if (v == 1) {
    	fwrite(&size, sizeof(int), 1, out);
    	fwrite(&v, sizeof(int), 1, out);
    } else {
    	fwrite(&size, sizeof(int), 1, out);
    	fwrite(&size, sizeof(int), 1, out);
    }

    double div = RAND_MAX / (double)(upper - lower);

	//writes values
	if (v == 1) {
		for (i = 0; i < size; i++) {
		    randnum = (double)lower + (rand() / div);
		    fwrite(&randnum, sizeof(double), 1, out);
		}
	} else {
		for (i = 0; i < size*size; i++) {
		    randnum = (double)lower + (rand() / div);
		    fwrite(&randnum, sizeof(double), 1, out);
		}
	}
	
    fclose(out);

    return 0;

}
