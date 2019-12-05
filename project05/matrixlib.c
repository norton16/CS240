#include "matrixlib.h"


/*
RESOURCES:
==========

0. read/write a float from/to a binary file:
        https://stackoverflow.com/a/1422854
        https://stackoverflow.com/a/21213612
        http://www.cplusplus.com/reference/cstdio/fread/
        http://www.cplusplus.com/reference/cstdio/fwrite/
1. identity matrices:
        https://www.mathbootcamps.com/the-identity-matrix-and-its-properties/
        https://www.khanacademy.org/math/precalculus/x9e81a4f98389efdf:matrices/x9e81a4f98389efdf:properties-of-matrix-multiplication/a/intro-to-identity-matrices
2. matrix addition:
        https://en.wikipedia.org/wiki/Matrix_addition#Entrywise_sum
3. matrix multiplication:
        https://www.mathsisfun.com/algebra/matrix-multiplying.html
        https://www.mathbootcamps.com/multiplying-matrices/
        https://www.khanacademy.org/math/precalculus/x9e81a4f98389efdf:matrices/x9e81a4f98389efdf:multiplying-matrices-by-matrices/a/multiplying-matrices
4. matrix inversion:
        https://www.mathportal.org/linear-algebra/matrices/gauss-jordan.php
*/


/*
IMPORTANT:
==========

0. You have got a helper function: print_matrix(.), which is defined in matrixlib.h.
   You may find it helpful for debugging purposes;

1. For every function that returns a matrix* (pointer to struct matrix), you need to allocate memory for the matrix first.
   And then you need to allocate memory for the data array of the matrix.
   Do not forget that data is a pointer to a 2D array.
   Review the previous lectures and labs for instructions on how to allocate memory for 2D arrays.

2. Do not free any memory in any function except the free_matrix(.) function

3. At the end of each test case, we will call the free_matrix(.) function on
   all the matrices involved in that test case (except for task# 1 and task# 2).
   So, even if your implementation of a certain function is correct,
   you will fail the test case(s) if your free_matrix(.) is faulty.
   Use valgrind to check for possible memory leaks;

4. There will be some test cases where we first load the argument matrices using the load_matrix_from_file(.) function and
   then pass those arguments to your function.
   If your implementation of load_matrix_from_file(.) is faulty, you will not pass those test cases.

5. In somr of the test cases, we call the previous functions implemented by you.
   You will not pass those cases if the previous tasks are not done properly.
*/

//void main(){}

matrix* load_matrix_from_file(const char *filename)
{
    matrix* m = (matrix*)malloc(sizeof(matrix));
    FILE* file = fopen(filename, "rb");

    if(file == NULL || ferror(file)){
        return NULL;
    }

    unsigned int x;
    fread((void*)&x, sizeof(unsigned int), 1, file);
     if(ferror(file)){
            return NULL;
        }
    m->nrows = x;
    fread((void*)&x, sizeof(unsigned int), 1, file);
     if(ferror(file)){
            return NULL;
        }
    m->ncols = x;

    m->data = (float **)malloc(m->nrows * sizeof(float *)); 
    for (int i=0; i<m->nrows; i++){ 
          m->data[i] = (float *)malloc(m->ncols * sizeof(float)); 
    }

    float v;
    for (int i = 0; i < m->nrows; ++i)
    {
        for(int j = 0; j < m->ncols; ++j){
            fread((void*)(&v), sizeof(v), 1, file);
             if(ferror(file)){
            return NULL;
        }
            m->data[i][j] = v;
        }
    }
    fclose(file);
    return m;
}

int save_matrix_to_file(matrix* matrix_to_save, const char *filename)
{
    FILE* file = fopen(filename, "wb");
    if(file == NULL || ferror(file)){
        return 0;
    } 
    fwrite((void*)&matrix_to_save->ncols, sizeof(unsigned int), 1, file);
    fwrite((void*)&matrix_to_save->nrows, sizeof(unsigned int), 1, file);
    for (int i=0; i<matrix_to_save->nrows; ++i){
    fwrite((void*)&matrix_to_save->data[i], sizeof(matrix_to_save->data[i][0]), matrix_to_save->ncols, file);
     if(ferror(file)){
            return 0;
        }
    }
    fclose(file);
    return 1;
}

int free_matrix(matrix* matrix_to_free)
{
    if(matrix_to_free == NULL){
        return 0;
    }
    // realloc(matrix_to_free, 0);
    for (int i = 0; i < matrix_to_free->nrows; i++)
    {
    free(matrix_to_free->data[i]);
    }
    free(matrix_to_free->data);
    free(matrix_to_free);
    return 1;
}

matrix* get_constant_matrix(int nrows, int ncols, const float value)
{
    matrix* m = (matrix*)malloc(sizeof(matrix));
    m->nrows = nrows;
    m->ncols = ncols;
    m->data = (float **)malloc(m->nrows * sizeof(float *)); 
    for (int i=0; i<nrows; i++){ 
          m->data[i] = (float *)malloc(ncols * sizeof(float)); 
    }

    for (int i = 0; i < nrows; i++)
    {
        for(int j = 0; j < ncols; j++){
            m->data[i][j] = value;
        }
    }
    return m;
}

matrix* get_identity_matrix(int dimension)
{
    matrix* m = (matrix*)malloc(sizeof(matrix));
    m->nrows = dimension;
    m->ncols = dimension;
    m->data = (float **)malloc(dimension * sizeof(float *)); 
    for (int i=0; i<dimension; i++){ 
          m->data[i] = (float *)malloc(dimension * sizeof(float)); 
    }

    for (int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++){
             if (i == j){
                m->data[i][j] = 1;
             }else{
                m->data[i][j] = 0;
             }
        }
    }
    return m;
}

matrix* get_sum_matrix(matrix* matrix_1, matrix* matrix_2)
{
    if(matrix_1->nrows != matrix_2->nrows || matrix_1->ncols != matrix_2->ncols){
        return NULL;
    }

    matrix* sm = (matrix*)malloc(sizeof(matrix));
    sm->nrows = matrix_1->nrows;
    sm->ncols = matrix_2->ncols;
    sm->data = (float **)malloc(sm->nrows * sizeof(float *)); 
    for (int i=0; i<sm->nrows; i++){ 
          sm->data[i] = (float *)malloc(sm->ncols * sizeof(float)); 
    }

    for (int i = 0; i < matrix_1->nrows; i++)
    {
        for(int j = 0; j < matrix_1->ncols; j++){
             sm->data[i][j] = (matrix_1->data[i][j] + matrix_2->data[i][j]);
        }
    }
    return sm;
}

matrix* get_difference_matrix(matrix* matrix_1, matrix* matrix_2)
{
    if(matrix_1->nrows != matrix_2->nrows || matrix_1->ncols != matrix_2->ncols){
        return NULL;
    }
    matrix* sm = (matrix*)malloc(sizeof(matrix));
    sm->nrows = matrix_1->nrows;
    sm->ncols = matrix_2->ncols;
    sm->data = (float **)malloc(sm->nrows * sizeof(float *)); 
    for (int i=0; i<sm->nrows; i++){ 
          sm->data[i] = (float *)malloc(sm->ncols * sizeof(float)); 
    }
    
    for (int i = 0; i < matrix_1->nrows; i++)
    {
        for(int j = 0; j < matrix_1->ncols; j++){
             sm->data[i][j] = (matrix_1->data[i][j] - matrix_2->data[i][j]);
        }
    }
    return sm;
}

matrix* get_product_matrix(matrix* matrix_1, matrix* matrix_2)
{
    if(matrix_1->ncols != matrix_2->nrows){
        return NULL;
    }
    matrix* sm = (matrix*)malloc(sizeof(matrix));
    sm->nrows = matrix_1->nrows;
    sm->ncols = matrix_2->ncols;
    sm->data = (float **)malloc(sm->nrows * sizeof(float *)); 
    for (int i=0; i<sm->nrows; i++){ 
          sm->data[i] = (float *)malloc(sm->ncols * sizeof(float)); 
    }

    for(int i=0; i<matrix_1->nrows; ++i){
        for(int j=0; j<matrix_2->ncols; ++j){
            sm->data[i][j] = 0.0f;
            for(int k=0; k<matrix_1->ncols; ++k)
            {
                sm->data[i][j] += (matrix_1->data[i][k]*matrix_2->data[k][j]);
            }
        }
    }
    return sm;
}

/*
********************************************************************************
********************************* EXTRA CREDIT *********************************
********************************************************************************
*/
unsigned int rr;
unsigned int cc;
void cofactor(float m[rr][cc], float temp[rr][cc], int p, int q, int n) 
{ 
    int i = 0; 
    int j = 0; 

    for (int row = 0; row < n; row++){ 
        for (int col = 0; col < n; col++){ 
            if (row != p && col != q){ 
                temp[i][j++] = m[row][col]; 
                if (j == (n-1)){ 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 

int determinant(float m[rr][cc], int n) 
{ 
    int D = 0;
    if (n == 1){ 
        return m[0][0];
    } 
  
    float t[rr][cc];
    int sign = 1;
    for (int f = 0; f < n; f++) 
    { 
        cofactor(m, t, 0, f, n); 
        D += (sign * m[0][f] * determinant(t, n - 1)); 
        sign = -sign; 
    } 
    return D; 
} 

void adjoint(float m[rr][cc], float adj[rr][cc]) 
{ 
    int sign = 1; 
    float t[rr][cc]; 

    if (rr == 1) 
        { 
            adj[0][0] = 1; 
            return; 
        } 
        
    for (int i=0; i<rr; i++) 
    { 
        for (int j=0; j<cc; j++) 
        {
            cofactor(m, t, i, j, rr);  
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j][i] = (float)((sign)*(determinant(m, rr-1))); 
        } 
    } 
} 

matrix* get_inverse_matrix(matrix* matrix_to_invert)
{ 
    rr = matrix_to_invert->nrows;
    cc = matrix_to_invert->ncols;
    float md[rr][cc];
    for (int i=0; i<rr; i++) 
    { 
        for (int j=0; j<cc; j++) 
        {
            md[i][j] = matrix_to_invert->data[i][j]; 
        } 
    } 

    if(determinant(md, rr) == 0){
        return NULL;
    }

    matrix* sm = (matrix*)malloc(sizeof(matrix));
    sm->nrows = matrix_to_invert->nrows;
    sm->ncols = matrix_to_invert->ncols;
    sm->data = (float **)malloc(sm->nrows * sizeof(float *)); 
    for (int i=0; i<sm->nrows; i++){ 
          sm->data[i] = (float *)malloc(sm->ncols * sizeof(float)); 
    }

    float adj[rr][cc];
    adjoint(md, adj);
	 for (int i=0; i<rr; i++){ 
        for (int j=0; j<cc; j++){ 
            sm->data[i][j] = (adj[i][j]/(float)determinant(md, rr));
        }
     } 

   return sm;
}
