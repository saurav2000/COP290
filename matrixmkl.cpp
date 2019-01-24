#include "matrixmkl.h"
#include "library.h"
#include "mkl.h"

void matrix_multiply_mkl(float* A, float* B, float* C, int m, int k)
{
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, 1, k, 1, A, k, B, 1, 0, C, 1);
}