#include "menu.h"
#include "matrix.h"

#define BUFF_LEN 256



int size = 0;
all_matrix *matrices;

int main(int argc, char **argv){
    srand(time(NULL));
    char choice;
    
    do{
        print_main_menu();
        scanf("%c", &choice);
        getc(stdin);
        switch(choice){
            case '1':
            {
                printf("Choose one of the following:\n1.Reset matrix array\n2.Add new matrix\n3.Add matrix from file\n4.Init random matrices(only when initializing)\n5.Exit\n>> ");
                scanf("%c", &choice);
                switch(choice){
                    case '1':
                    {
                        get_matrices(stdin, NORANDOM);
                        break;
                    }
                    case '2':
                    {
                        append_matrix();
                        break;
                    }
                    case '3':
                    {
                        char path[BUFF_LEN];
                        printf("Enter File Path:\n>> ");
                        scanf("%s", path);
                        FILE *fd = fopen(path, "r");
                        if(fd)
                            get_matrices(fd, NORANDOM);
                        else
                            printf("Try again!\n");
                        break;
                    }
		    case '4':
			get_matrices(stdin, RANDOM);
                    case '5':
                        break;
                    default:
                    {
                        printf("Try again!\n");
                        break;
                    }
                }
                break;
            }
            case '2':
            {
                print_ariphmetic_menu();
                choice = 0;
                scanf("%c", &choice);
                getc(stdin);

                int i,j;
                int n1, n2, m1, m2;
                switch(choice){
                    case '1':{
                        printf("You entered %d matrices, select two of them (i, j):\n>>", size);
                        scanf("%d %d", &i, &j);
                        getc(stdin);

                        if(matrices[i-1].n != matrices[j-1].n || matrices[i-1].m != matrices[j-1].m)
                            printf("Ok, give you another chance. Try it again!\n");
                        else{
                            add_matrices(i-1, j-1);
                            print_res(i - 1);
                        }
                        continue_line();
                        break;
                    }
                    case '2':
                    {
                        printf("You have %d matrices, select two of them (i, j)\n>> ", size);
                        scanf("%d %d", &i, &j);
                        if(matrices[i - 1].m != matrices[j - 1].n){
                            printf("Can't multiply these because of different sizes!\n");
                        } else {
                            multiply_matrix(i - 1, j - 1);
                            print_res(size - 1);
                        }
                        break;
                    }
                    case '3':
                    {
                        printf("You have %d matrices, select one of them (i)\n>> ", size);
                        scanf("%d", &i);
                        getc(stdin);
                        transpose_matrix(i-1);
                        print_res(i - 1);
                        continue_line();
                        break;
                    }
                    case '4':
                    {
                        printf("You have %d matrices, select one of them (i)\n>> ", size);
                        scanf("%d", &i);
                        if(matrices[i-1].n != matrices[i-1].m)
                            printf("Cant find an inverse of non square matrix\n>> ");
                        else{
                            float det = find_determinant(matrices[i-1].matrix, matrices[i-1].n);
                            if(det != 0){
                                find_inverse(i - 1, det);
                                print_matrix(size - 1);
                            }
                        }
                        break;
                    }
                    case '5':
                        break;
                    default:
                    {
                        printf("Ok, give you another chance. Try it again!\n");
                        break;
                    }
                }
                break;
            }
            case '3':
            {
                print_all_matrices();
                continue_line();
                break;
            }
            case '4':
            {
                if(size != 0){
                    char path[BUFF_LEN];
                    printf("Enter path, note it will overwrite the file:\n>> ");
                    scanf("%s", path);
                    FILE *fd = fopen(path, "w");
                    if(fd)
                        write_to_file(fd);
                    else
                        printf("Try again!\n");
                    fclose(fd);
                }
                else
                    printf("Nothing to write!\n");
                break;
            }
            default:
            {
                printf("Ok, give you another chance. Try it again!\n");
                printf("Enter any key to exit...");
		break;
            }
        }
        getc(stdin);
    } while(choice != 'e');
    free_array();
    return 1;
}
