#include "defs.h"
#include "library.h"
#include <cblas.h>
#include "matrixmkl.h"
using namespace std::chrono;

vector<vf> toeplitz_matrix;
vf kern_column;
vf res_line;

struct thread_data
{
	int tid;
	int tot;
};

void padding(vector<vf> &img, int pad)
{
	int n=img.size();
	vf zero1(n+2*pad,0.0f);
	vf zero2(pad,0.0f);

	for(int i=0;i<img.size();++i)
	{
		img[i].insert(img[i].begin(), zero2.begin(), zero2.end());
		img[i].insert(img[i].end(), zero2.begin(), zero2.end());
	}

	img.insert(img.begin(),pad,zero1);
	img.insert(img.end(),pad,zero1);
}

void matrix_multiply_openblas(float* A, float* B, float* C)
{
	int m = toeplitz_matrix.size();
	int k = kern_column.size();
	

	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, 1, k, 1, A, k, B, 1, 0, C, 1);
}

void matrix_multiply_normal()
{
	int a=toeplitz_matrix.size();
	int b=kern_column.size();
	for(int i=0;i<a;i++)
	{
		float sum=0.0f;
		for(int j=0;j<b;j++)
		{
			sum+=kern_column[j]*toeplitz_matrix[i][j];
		}
		res_line[i]=sum;
	}
}

void* thread_routine(void* arg)
{
	
	thread_data* data = (thread_data*)arg;
	for(int i=data->tid;i<min((int)toeplitz_matrix.size(),(data->tid)+(data->tot));++i)
	{
		float sum=0.0f;
		for(int j=0;j<kern_column.size();j++)
		{
			sum+= toeplitz_matrix[i][j] * kern_column[j];
		}
		res_line[i]=sum;
	}
	
}

void matrix_multiply_pthread()
{
	int N = toeplitz_matrix.size();
	pthread_t threads[Nmax];
	thread_data *td;
	td= new thread_data[Nmax];
	int j=0,i=0;
	int y=((N-1)/Nmax)+1;
	for(i=0;i<Nmax;i++)
	{
		td[i].tid=j;
		td[i].tot=y;
		// cout<<j<<endl;
		int thread_error = pthread_create(&threads[i],NULL ,thread_routine, (void*) &td[i]);
		if(thread_error)
			cout<<"Thread error\n";
		j+=y;
		if(j>=N)
			break;

	}
	
	for(int j=0;j<i;++j)
		pthread_join(threads[j], NULL);
}

void convolution_npad(vector<vf>& img, vector<vf>& kern, vector<vf>& res)
{
	int na=img.size();
	int nb=kern.size();
	float arr[na-nb+1][na-nb+1];

	for(int i=0;i<na-nb+1;++i)
	{
		for(int j=0;j<na-nb+1;++j)
		{
			float sum=0.0f;
			for(int m=0;m<nb;++m)
			{
				for(int n=0;n<nb;++n)
					sum+= img[m+i][n+j] * kern[nb-m-1][nb-n-1];
			}
			arr[i][j]=sum;
		}
	}

	for(int i=0;i<na-nb+1;++i)
	{
		vf temp(arr[i], arr[i]+na-nb+1);
		res.pb(temp);
	}

} 

void convolution_pad(vector<vf>& img, vector<vf>& kern, int pad, vector<vf>& res)
{
	padding(img, pad);
	convolution_npad(img, kern, res);
}

void conv_matrmult_npad(vector<vf>& img, vector<vf>& kern, vector<vf>& res, int mode)
{
	int na=img.size();
	int nb=kern.size();
	int n=na-nb+1;

	kern_column.clear();
	toeplitz_matrix.clear();
	res_line.clear();
	kern_column.resize(nb*nb);
	toeplitz_matrix.resize(n*n, kern_column);
	res_line.resize(n*n);

	for(int i=nb-1,k=0;i>=0;--i)
	{
		for(int j=nb-1;j>=0;--j,++k)
			kern_column[k]=kern[i][j];
	}

	for(int i=0;i<na-nb+1;++i)
	{
		for(int j=0;j<na-nb+1;++j)
		{
			for(int k=0;k<nb;++k)
			{
				for(int l=0;l<nb;++l)
					toeplitz_matrix[j+i*n][l+k*nb]=img[i+k][j+l];
			}
		}
	}
	int m = toeplitz_matrix.size();
	int k = kern_column.size();
	float* A = (float*)malloc(m*k*sizeof(float));
	float* B = (float*)malloc(k*sizeof(float));
	float* C = (float*)malloc(m*sizeof(float));

	for(int i=0;i<m*k;++i)
		A[i] = toeplitz_matrix[i/k][i%k];
	for(int i=0;i<k;++i)
		B[i] = kern_column[i];
	for(int i=0;i<m;++i)
		C[i] = 0.0;
	auto startT = high_resolution_clock::now();
	// cout<<mode<<"\n";
	switch(mode)
	{
		case 1:
			matrix_multiply_normal();
			break;
		case 2:
			matrix_multiply_pthread();
			break;
		case 4:
		 	matrix_multiply_mkl(A, B, C, m, k);
			break;
		case 3:
			matrix_multiply_openblas(A,B,C);
	}
	auto stopT = high_resolution_clock::now();
	auto elapsed_seconds = duration_cast<microseconds>(stopT - startT);
	cout<<elapsed_seconds.count()<<"\n";
	
	if(mode==3||mode==4)
	{
		for(int i=0;i<m;++i)
			res_line[i] = C[i];
	}
	for(int i=0;i<n;++i)
	{
		vf temp2(res_line.begin()+i*n, res_line.begin()+(i+1)*n);
		res.pb(temp2);
	}

	// cout<<"why>";

}

void conv_matrmult_pad(vector<vf>& img, vector<vf>& kern, int pad, vector<vf>& res,int mode)
{
	padding(img, pad);
	
	conv_matrmult_npad(img, kern, res, mode);
}