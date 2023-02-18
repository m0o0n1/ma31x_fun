#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "headers.h"
#include "menu.h"

void print_matrix(int);
void print_all_matrices();
void get_matrices(FILE *, char);
void add_matrices(int, int);
void transpose_matrix(int);
void multiply_matrix(int a, int b);
void append_matrix();
void continue_line();
void print_res(int);
float find_determinant(float**, int);
void find_inverse(int, float);
void write_to_file(FILE*);

void free_array();


#endif
