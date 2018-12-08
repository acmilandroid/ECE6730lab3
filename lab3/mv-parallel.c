/*******************
 * Basil Lin
 * ECE 6730
 * mv-serial.c
 *******************/
 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

int main(int argc, char **argv) {

    FILE *fpt1, *fpt2, *out;
    int i, j, r1, c1, r2, c2;
    double partial_sum;
    
    if ((fpt1 = fopen(argv[1], "rb")) == NULL) {
		printf("Unable to open %s for reading\n", argv[2]);
		exit(0);
	}
    if ((fpt2 = fopen(argv[2], "rb")) == NULL) {
		printf("Unable to open %s for reading\n", argv[3]);
		exit(0);
	}
    if ((out = fopen(argv[3], "wb")) == NULL) {
		printf("Unable to open %s for writing\n", argv[4]);
		exit(0);
	}

	//reads file dimensions
	fread(&r1, sizeof(int), 1, fpt1);
	fread(&c1, sizeof(int), 1, fpt1);
	fread(&r2, sizeof(int), 1, fpt2);
	fread(&c2, sizeof(int), 1, fpt2);
    
    if (c1 != r2) {
    	printf("Dimension mismatch. Exiting.\n");
    	exit(0);
    }
    if (c2 != 1) {
    	printf("Not a matrix and a vector. Exiting.\n");
    	exit(0);
    }
    
    double *matrix = (double *)malloc(sizeof(double) * r1 * r1);
    double *vector = (double *)malloc(sizeof(double) * r2);
    double *out_vector = (double *)malloc(sizeof(double) * r1);
    
    //reads file data
    for (i = 0; i < r1*r1; i++) {
    	fread(&matrix[i], sizeof(double), 1, fpt1);
    }
    for (i = 0; i < r2; i++) {
    	fread(&vector[i], sizeof(double), 1, fpt2);
    }
    
    //write output dimensions
    fwrite(&r2, sizeof(int), 1, out);
    fwrite(&c2, sizeof(int), 1, out);

	//start timing
	struct timeval start, end;
	gettimeofday(&start, NULL);

	//multiply
	#pragma omp parallel for private(j)
    for (i = 0; i < r1; i++) {
    	partial_sum = 0;
    	#pragma omp parallel reduction(+:partial_sum)
    	for (j = 0; j < r1; j++) {
    		partial_sum += matrix[i*r1+j] * vector[j];
    		out_vector[i] = partial_sum;
    	}
    }

	//end timing
	gettimeofday(&end, NULL);
	double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
	
	printf("Executed in %lf seconds.\n", delta);
	
	for (i = 0; i < r1; i++) {
		fwrite(&out_vector[i], sizeof(double), 1, out);
    }
    	
    //cleanup
    fclose(fpt1);
    fclose(fpt2);
    fclose(out);
    
    return 0;

}
