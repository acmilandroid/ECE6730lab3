/*********************
 * Basil Lin
 * ECE 6730
 * print-matrix.c
 *********************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(int argc, char **argv) {
    FILE *fpt;
    int i, j, n;
    int type;
    double num;

    if ((fpt = fopen(argv[1], "rb")) == NULL) {
        printf("Unable to open %s for reading\n", argv[1]);
		exit(0);
    }

	//read dimensions
    fread(&n, sizeof(int), 1, fpt);
    fread(&type, sizeof(int), 1, fpt);

	//print data
    printf("\n");
    if (type == 1) {
        for (i = 0; i < n; i++) {
            fread(&num, sizeof(double), 1, fpt);
            printf("%lf\n", num);
        }
    } else {
        for (j = 0; j < n; j++) {
            for (i = 0; i < n; i++) {
                fread(&num, sizeof(double), 1, fpt);
                printf("%lf ", num);
            }
            printf("\n");
        }
    }
    printf("\n");
    
    return 0;
}
