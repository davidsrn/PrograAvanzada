/*----------------------------------------------------------------

*

* Programación avanzada: Apuntadores y arreglos

* Fecha: 15-Ago-2018

* Autor(es): A01206423 David Ramirez
						 A01206747 Filiberto Vázquez

*

*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct {
	double *data;
	uint nrows, ncols;
} Matrix;

void printm(Matrix *M) {
	// printf("Here you have to display the matrix with the format:\n");
	// printf(" a0,0 a0,1 ... a0,n-1,\n");
	// printf(" a1,0 a1,1 ... a0,n-1,\n");
	// printf(" ...\n");
	// printf(" an-1,1 an-1,2 ... an-1,n-1\n");
	uint i, j;
	 for(i = 0; i < M->nrows; i ++){
			printf("\t");
			for(j = 0; j < M->ncols; j++){
				printf("%f ", M->data[i*M->ncols+j]);
			}
			printf("\n");
	 }
}


//MEMORY ALLOCATION FUNCTION
Matrix* alloc_matrix(uint nrows, uint ncols) {
	/****************************************
	 * This procedure should request the amount of memory
	 * needed for the Matrix structure and for the storage
	 * of a matrix of the required dimensions. If you can
	 * not get that amount of memory, return NULL.
	 * Check that nrows and ncols must be greater than 0.
	 * If you have allocated memory and there is an error,
	 * you must free all the memory allocated.
	 ****************************************/
  Matrix *M;

  M=(Matrix *)malloc(sizeof(Matrix));

  if(!M) return NULL;

	if(nrows<=0||ncols<=0){
		printf("%s\n", "Values should be bigger that 0");
		return NULL;
	}


  M->nrows=nrows;
  M->ncols=ncols;
  M->data=(double *)malloc((nrows*ncols)*sizeof(*M->data));

	if(M->data==NULL){
		free(M);
		return NULL;
	}

  return M;
}

void set(Matrix *M, uint row, uint col, double val) {
	/****************************************
	 * Check that the rung and column is valid for the matrix,
	 * if not, it displays an error. Otherwise, place the value
	 * in the correct cell. Check the following links:
	 * https://stackoverflow.com/questions/2151084/map-a-2d-array-onto-a-1d-array
	 * https://stackoverflow.com/questions/14015556/how-to-map-the-indexes-of-a-matrix-to-a-1-dimensional-array-c
	 ****************************************/
  if(M != NULL){
	  M->data[row*M->ncols+col]=val;
	  if(row < 0 || row > M->nrows || col < 0 || col > M->ncols){
		  printf("%s\n", "Invalid position recieved");
	  }
  }else{
		printf("%s\n", "Invalid Matrix");
	}
}

void matrix_mult(Matrix *A, Matrix *B, Matrix *C) {
	/****************************************
	 * It must be checked that the multiplication can be done
	 * (check the following links:
	 * https://es.wikipedia.org/wiki/Multiplicaci%C3%B3n_de_matrices
	 * https://www.geogebra.org/m/S6R8A2xD
	 * ). If it can not be done, you must display an error message.
	 * Remember check for null pointer.
	 *
	 * The multiplication is A x B = C
	 ****************************************/
	if(A != NULL && B != NULL && C != NULL){
		uint i, j, k;
		double sum = 0;
		if(A->ncols==B->nrows){
			if((C->nrows==A->nrows) && (C->ncols=B->ncols)){
				for(i = 0; i < A->nrows; i ++){
					for(j = 0; j < B->ncols; j++){
						sum = 0;
						for(k = 0; k < B->nrows; k ++){
							sum += A->data[i * A->ncols + k]*B->data[k * B->ncols + j];
							C->data[i * C->ncols + j] = sum;
						}
					}
				}
			}
		}else{
			printf("\nCannot multiply since A rows != to B cols");
		}
	}else{
		printf("%s\n", "NULL Matrix received");
	}
}

void free_matrix(Matrix *M) {
	/****************************************
	 * If the element that is received is different from NULL,
	 * the space assigned to the array and the structure must be
	 * freed.
	 ****************************************/

	if(M != NULL){
		free(M);
	}else{
		printf("%s\n", "Invalid Matrix");
	}
}


int main(int argc, char* argv[]) {
	printf("Creating the matrix A:\n");
	Matrix *A = alloc_matrix(3, 2);

	printf("Setting the matrix A:\n");
	set(A, 0, 0, 1.2);
	set(A, 0, 1, 2.3);
	set(A, 1, 0, 3.4);
	set(A, 1, 1, 4.5);
	set(A, 2, 0, 5.6);
	set(A, 2, 1, 6.7);
	printf("Printing the matrix A:\n");
	printm(A);

	printf("Creating the matrix B:\n");
	Matrix *B = alloc_matrix(2, 3);
	printf("Setting the matrix B:\n");
	set(B, 0, 0, 5.5);
	set(B, 0, 1, 6.6);
	set(B, 0, 2, 7.7);
	set(B, 1, 0, 1.2);
	set(B, 1, 1, 2.1);
	set(B, 1, 2, 3.3);
	printf("Printing the matrix B:\n");
	printm(B);

	printf("Creating the matrix C:\n");
	Matrix *C = alloc_matrix(3, 3);
	printf("A x B = C:\n");
	matrix_mult(A, B, C);
	printf("Printing the matrix C:\n");
	printm(C);

	printf("B x A = C:\n");
	matrix_mult(B, A, C);
	printf("Printing the matrix C:\n");
	printm(C);

	Matrix *D = NULL;
	printf("Setting a NULL matrix (D):\n");
	set(D, 0, 0, 10);

	printf("A x D(NULL) = C:\n");
	matrix_mult(A, D, C);
	printf("D(NULL) x A = C:\n");
	matrix_mult(D, A, C);

	printf("Allocating E with (0,0): \n");
	Matrix *E = alloc_matrix(0, 0);

	printf("Freeing A:\n");
	free_matrix(A);
	printf("Freeing B:\n");
	free_matrix(B);
	printf("Freeing C:\n");
	free_matrix(C);
	printf("Freeing D(NULL):\n");
	free_matrix(D);
	printf("Freeing E(NULL):\n");
	free_matrix(E);

	return 0;
}
