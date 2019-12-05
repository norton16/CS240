#include <stdio.h>
#include <stdlib.h>

struct matrix
{
    /*
    nrows is the number of rows in the matrix (i.e., height of the matrix)

    ncols is the number of columns in the matrix (i.e., width of the matrix)

    data is a pointer to an array of float*
    basically a pointer to a 2D array
    the actual container of the entries in the matrix
    */

    unsigned int nrows;
    unsigned int ncols;
    float **data;
};
typedef struct matrix matrix; /* now we will be able to use "matrix" in stead of "struct matrix" */

matrix* load_matrix_from_file(const char *filename);

int save_matrix_to_file(matrix* matrix_to_save, const char *filename);

int free_matrix(matrix* matrix_to_free);

matrix* get_constant_matrix(int nrows, int ncols, const float value);

matrix* get_identity_matrix(int dimension);

matrix* get_sum_matrix(matrix* matrix_1, matrix* matrix_2);

matrix* get_difference_matrix(matrix* matrix_1, matrix* matrix_2);

matrix* get_product_matrix(matrix* matrix_1, matrix* matrix_2);

/*
********************************************************************************
********************************* EXTRA CREDIT *********************************
********************************************************************************
*/
matrix* get_inverse_matrix(matrix* matrix_to_invert);

/*
********************************************************************************
******************************* HELPER FUNCTIONS *******************************
********************************************************************************
*/

// DO NOT CHNAGE THIS!
int print_matrix(matrix* matrix_to_print)
{
    if(!matrix_to_print)
    {
         printf("Invalid Matrix\n");
         return 0;
    }

    float **data = matrix_to_print->data;

    for (unsigned int row = 0; row < matrix_to_print->nrows; row++)
    {
        for (unsigned int col = 0; col < matrix_to_print->ncols; col++)
        {
            printf("%10.2f", data[row][col]);
        }
        printf("\n");
    }
    printf("\n\n");

    return 1;
}