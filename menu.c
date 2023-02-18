#include "menu.h"

void print_main_menu(){
    printf("Matrix Fun\n");
    print_line();
    printf("Enter number what you want program to do\n");
    printf("1. Enter matrix\n");
    printf("2. Matrix ariphmetic\n");
    printf("3. Print all matrices\n");
    printf("4. Print this hit in file\n>> ");
}

void print_line(){
    printf("=====================================================================\n");
}

void print_ariphmetic_menu(){
    print_line();
    printf("ALL OPERATIONS WILL BE STORED IN FIRST OPERAND, EXCEPT 2!\n");
    print_line();
    printf("1. Addition\n");
    printf("2. Multiplication\n");
    printf("3. Transpose\n");
    printf("4. Inverse\n");
    printf("5. Exit\n>> ");
}