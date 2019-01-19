#include "defs.h"
#include "library.h"

struct thread_data
{
	int tid;
	vf v1;
	vf v2;
	vf* res;
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

void matrix_multiply(vector<vf>& v1, vf& v2, vf& res)
{
	int a=v1.size();
	int b=v2.size();
	for(int i=0;i<a;++i)
	{
		float sum=0.0f;
		for(int j=0;j<b;++j)
			sum+=v1[i][j]*v2[j];
		res.pb(sum);
	}
}

void* thread_routine(void* arg)
{
	float sum=0.0f;
	thread_data* data = (thread_data*)arg;
	for(int i=0;i<data->v1.size();++i)
		sum+= data->v1[i]*data->v2[i];
	
	vf* temp=data->res;
	(*temp).at(data->tid)=sum;
}

void matrix_multiply_pthread(vector<vf>& v1, vf& v2, vf* res,int x)
{
	int N = v1.size();
	pthread_t threads[Nmax];
	thread_data *td;
	td= new thread_data[Nmax];
	int j=0;
	for(int i=x;i<min(N,Nmax+x);++i,++j)
	{
		td[j].tid=i;
		td[j].v1=v1[i];
		td[j].v2=v2;
		td[j].res = res;
		int thread_error=pthread_create(&threads[j], NULL, thread_routine, (void*) &td[j]);
		if(thread_error)
			cout<<"Thread error\n";
	}
	for(int i=0;i<j;++i)
		pthread_join(threads[i], NULL);
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

void conv_matrmult_npad(vector<vf>& img, vector<vf>& kern, vector<vf>& res)
{
	int na=img.size();
	int nb=kern.size();
	int n=na-nb+1;
	vf kern_column;
	vector<vf> tmatrix;


	for(int i=0;i<nb;++i)
	{
		for(int j=0;j<nb;++j)
			kern_column.pb(kern[nb-i-1][nb-j-1]);
	}

	for(int i=0;i<na-nb+1;++i)
	{
		for(int j=0;j<na-nb+1;++j)
		{
			vf temp;
			for(int m=0;m<nb;++m)
			{
				for(int n=0;n<nb;++n)
					temp.pb(img[i+m][j+n]);
			}
			tmatrix.pb(temp);
		}
	}

	vf line(n*n,0);
	// vf line;
	int x=n*n;
	int pt=0;
	while(x>0)
	{
		matrix_multiply_pthread(tmatrix, kern_column, &line,pt);
		x-=Nmax;
		pt+=Nmax;
	}
	// matrix_multiply(tmatrix, kern_column, line);
	for(int i=0;i<n;++i)
	{
		vf temp2(line.begin()+i*n, line.begin()+(i+1)*n);
		res.pb(temp2);
	}

}

void conv_matrmult_pad(vector<vf>& img, vector<vf>& kern, int pad, vector<vf>& res)
{
	padding(img, pad);
	conv_matrmult_npad(img, kern, res);
}