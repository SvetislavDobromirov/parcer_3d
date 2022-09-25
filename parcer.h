#ifndef PARCER_H
#define PARCER_H
#include <stdio.h>
#include <stdlib.h>




typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;

typedef struct facets {
	int *vertexes;
	int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
    unsigned long count_of_v;
    unsigned long count_of_f;
    matrix_t matrix_3d;
	polygon_t *polygons; // выдеется память по f
} struct_data;

int counter_f_v(struct_data* data, char* filename);
int start_parcer(struct_data* data, char* filename);
int parcer_main(struct_data* data, char* filename);
int count_num_in_poly(char *str);


#endif // PARCER_H
