#include "matrix.h"

void print_res(int ind){
    printf("The result is:\n");
    print_matrix(ind);
}

void continue_line(){
    printf(">> Press any key...");
}

void print_matrix(int a){
    for(int i = 0; i < matrices[a].m; i++){
        for(int j = 0; j < matrices[a].n; j++)
            printf("%f ", matrices[a].matrix[i][j]);
        printf("\n");
    }
}

void print_all_matrices(){
    if(size != 0){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < matrices[i].m; j++){
                for(int k = 0; k < matrices[i].n; k++){
                    printf("%f ", matrices[i].matrix[j][k]);
                }
                printf("\n");
            }
            if(i != size - 1){
                printf("\n");
            }
        }
    } else{
        printf("You haven't entered any matrix yet, dummy\n");
    }
}

void write_to_file(FILE *fd){
    for(int i = 0; i < size; i++){
        fprintf(fd, "%d %d\n", matrices[i].m, matrices[i].n);
        for(int j = 0; j < matrices[i].m; j++){
            for(int k = 0; k < matrices[i].n; k++){
                fprintf(fd, "%f ", matrices[i].matrix[j][k]);
            }
            fprintf(fd, "\n");
        }
        fprintf(fd, "\n");
    }
}

void get_matrices(FILE *fd, char is_random){
    printf("Enter number of matrices first of all\n>> ");
    fscanf(fd, "%d", &size);
    

    matrices = (all_matrix *)malloc(sizeof(all_matrix) * size);
    print_line();

    for(int i = 0; i < size; i++){
        int n, m;
        printf("Enter %d matrix size (m x n):\n>> ", i+1);
        fscanf(fd, "%d %d", &m, &n);
        matrices[i].n = n;
        matrices[i].m = m;
        matrices[i].matrix = (float **)malloc(m * sizeof(float*));
        for(int k = 0; k < m; k++)
            matrices[i].matrix[k] = (float *)malloc(n * sizeof(float));


        for(int k = 0; k < m; k++){
            if(!is_random)
	    	printf(">> ");
            for(int l = 0; l < n; l++){
		if(!is_random){
                	float num;
                	fscanf(fd, "%f", &num);
                	matrices[i].matrix[k][l] = num;
		} else if(is_random){
			matrices[i].matrix[k][l] = rand() % 128;
		}
            }
        }
    }
    print_line();
}

void allocate_new(int start, int count){
    for(int i = 0; i < count; i++){
        int n, m;
        printf("Enter %d matrix size (m x n):\n>> ", i+1);
        scanf("%d %d", &m, &n);
        matrices[start + i].n = n;
        matrices[start + i].m = m;
        matrices[start + i].matrix = (float **)malloc(m * sizeof(float*));
        for(int k = 0; k < m; k++)
            matrices[start + i].matrix[k] = (float *)malloc(n * sizeof(float));

        printf("Now Enter Its Elements\n");
        for(int k = 0; k < m; k++){
            printf(">> ");
            for(int l = 0; l < n; l++){
                float num;
                scanf("%f", &num);
                getc(stdin);
                matrices[start + i].matrix[k][l] = num;
            }
        }
    }
}

void append_matrix(){
    if(size == 0){
        get_matrices(stdin, NORANDOM);
    } else{
        int car; 
        printf("Enter a number of matrices to add\n>> ");
        scanf("%d", &car); 

        matrices = (all_matrix*)realloc(matrices, sizeof(all_matrix)*(size + car));
        allocate_new(size, car);
        size += car;
    }
}

  /**************************************************************/
 /*ARIPHMETIC                                                  */
/**************************************************************/

void add_matrices(int a, int b){
    for(int i = 0; i < matrices[a].m; i++){
        for(int j = 0; j < matrices[a].n; j++){
            matrices[a].matrix[i][j] += matrices[b].matrix[i][j];
        }
    }
}

void transpose_matrix(int a){    
    float **temp = (float **)malloc(sizeof(float *) * matrices[a].n);
    for(int i = 0; i < matrices[a].n; i++)
        temp[i] = (float *)malloc(sizeof(float) * matrices[a].m);

    for(int i = 0; i < matrices[a].m; i++){
        for(int j = 0; j < matrices[a].n; j++){
           temp[j][i] = matrices[a].matrix[i][j];
        }
    }

    for(int i = 0; i < matrices[a].m; i++)
        free(matrices[a].matrix[i]);
    free(matrices[a].matrix);

    matrices[a].matrix = temp;
    int n = matrices[a].n;
    matrices[a].n = matrices[a].m;
    matrices[a].m = n;
}

void multiply_matrix(int a, int b){
        matrices = (all_matrix *)realloc(matrices, sizeof(all_matrix) * (size + 1));
        matrices[size].matrix = (float **)malloc(matrices[a].m * sizeof(float *));
        for(int i = 0; i < matrices[a].m; i++){
            matrices[size].matrix[i] = (float *)malloc(matrices[b].n * sizeof(float));
        }
        matrices[size].m = matrices[a].m;
        matrices[size].n = matrices[b].n;
        
        for(int i = 0; i < matrices[size].m; i++){
            for(int j = 0; j < matrices[size].n; j++){
                float sum = 0;
                for(int k = 0; k < matrices[a].n; k++){
                    sum += matrices[a].matrix[i][k] * matrices[b].matrix[k][j];
                }
                matrices[size].matrix[i][j] = sum;
            }
        }
        size++;
}

float get_alg(float **matrix, int n, int y, int x){
    float algebraic = 0;
    float **temp = (float **)malloc(sizeof(float *) * (n - 1));
    for(int i = 0; i < n - 1; i++)
        temp[i] = (float *)malloc(sizeof(float) * (n - 1));

    int rows = 0, cols = 0;
    for(int i = 0; i < n; i++){
        if(i != y){
            cols = 0;
            for(int j = 0; j < n; j++){
                if(j != x){
                    temp[rows][cols] = matrix[i][j];
                    cols++;
                }
            }
            rows++;
        }
    }

    int sign = 0;
    sign = (x + y) % 2 == 0 ? 1 : -1;
    algebraic = sign * find_determinant(temp, n - 1);
    for(int i = 0; i < n - 1; i++)
        free(temp[i]);
    free(temp);
    return fabs(algebraic) < FLT_EPSILON ? 0 : algebraic;
}

float find_determinant(float **matrix, int n){
    float det = 0;
    if(n == 1)
        return matrix[0][0];
    else if(n == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else{
        for(int i = 0; i < n; i++){
            det += matrix[0][i] * get_alg(matrix, n, 0, i);
        }
    }
    return det;
}

void find_inverse(int ind, float det){
    matrices = (all_matrix *)realloc(matrices, sizeof(all_matrix) * (size + 1));
    matrices[size].matrix = (float **)malloc(sizeof(float*) * matrices[ind].n);
    for(int i = 0; i < matrices[ind].n; i++)
        matrices[size].matrix[i] = (float *)malloc(sizeof(float) * matrices[ind].n);
   
    matrices[size].m = matrices[ind].m;
    matrices[size].n = matrices[ind].n;
    
    for(int i = 0; i < matrices[size].n; i++){
        for(int j = 0; j < matrices[size].m; j++){
            matrices[size].matrix[i][j] = (1.0f / det)*get_alg(matrices[ind].matrix, matrices[ind].n, i, j);
        }
    }
    transpose_matrix(size);
    size += 1;
}

void free_array(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < matrices[i].n; j++){
            free(matrices[i].matrix[j]);
        }
        free(matrices[i].matrix);
    }
    free(matrices);
}

