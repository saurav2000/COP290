#include "defs.h"
#include "library.h"

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
	vf line;
	matrix_multiply(tmatrix, kern_column, line);

	int n=na-nb+1;
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