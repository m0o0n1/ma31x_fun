#ifndef __HEADERS_H__
#define __HEADERS_H__

#define BUFF_LEN 256
#define NORANDOM 0
#define RANDOM 1


#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>

typedef struct _tagMatrix{
    float **matrix;
    int n;
    int m;
} all_matrix;

extern all_matrix *matrices;
extern int size;

#endif
