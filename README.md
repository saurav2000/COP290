## Running the code
- To compile the code run `make all` 
- Now run `./image` followed by the **argument given below** specific to the function

- To call Convolution with padding with matrix multiplication:
	 >  `convolution_withpadding_matrixmult [PADSIZE] MODE [matrix1.txt] [matrix1_numrows] [matrix2.txt] [matrix2_numrows]`
	 
- To call Convolution without padding with matrix multiplication:
	 >  `convolution_withoutpadding_matrixmult MODE [matrix1.txt] [matrix1_numrows] [matrix2.txt] [matrix2_numrows]`
> where MODE is 1 for normal multiplication, 2 for pthread, 3 for OpenBLAS, 4 for MKL.

- To call Convolution with padding with Convolution:
	> `convolution_withpadding_conv [PADSIZE] [matrix1.txt] [matrix1_numrows] [matrix2.txt] [matrix2_numrows]`

- To call Convolution without padding with Convolution:
	> `convolution_withoutpadding_conv [matrix1.txt] [matrix1_numrows] [matrix2.txt] [matrix2_numrows]`

- To call relu activation:
	> `activation_relu [matrix1.txt] [matrix1_numrows]`

- To call tanh activation:
	> `activation_tanh [matrix1.txt] [matrix1_numrows]`

- To do subsampling with maxpooling:
	> `subsampling_maxpooling [matrix1.txt] [matrix1_numrows]`

- To do subsampling with average pooling:
	> `subsampling_avgpooling [matrix1.txt] [matrix1_numrows]`

- To convert random float vector to probability vector using softmax:
	> `probability_softmax [matrix1.txt] [matrix1_numrows]`

- To convert random float vector to probability vector using sigmoid
	> `probability_sigmoid [matrix1.txt] [matrix1_numrows]`

## NOTE: 
- For sub-sampling (both odd and even) we have chosen the sampling matrix to be 2x2 and the stride to be 2 always.
- For Max pooling we padded the odd size matrices and for average pooling we considered the average of only two elements when we reached the edge of the matrix.
- For the convolution we inverted the kernel.

## NOTE FOR SUBTASK 2:
- We have tested the time of multiplication of the toeplitz matrix with pthread, openBLAS, mkl libraries against matrix of sizes 1000,900,750 & 500 and a kernel size of 3.
- If the range of the y-axis in the png file is too small, the ps file has a elongated version.
- The times in the graphs are in microseconds measured by the chrono high resolution clock.
- This Subtask prints the time taken by the matrix multiplication for the matrix_multiplication command and prints the resultant matrix or vector.
