#include<bits/stdc++.h>
using namespace std;

void nonLinearActivationRelu(float** ar)
{
	int n = sizeof(ar)/sizeof(ar[0]);
	int m = sizeof(ar[0])/sizeof(ar[0][0]);
	
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)
		{
			if(ar[i][j]<=0)
				ar[i][j]=0.0;
		}
	}
}

void nonLinearActivationTanh(float** ar)
{
	int n = sizeof(ar)/sizeof(ar[0]);
	int m = sizeof(ar[0])/sizeof(ar[0][0]);
	
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)
		{
			float temp=exp(-2*ar[i][j]);
			ar[i][j]=(1-temp)/(1+temp);
		}
	}
}

float** subsamplingMax(float** ar)
{
	int n = sizeof(ar)/sizeof(ar[0]);
	int m;
	if(n&1)
	m= n/2 + 1;
	else
	m=n/2;
	float res[n][n];
	for(int i=0;i<m; ++i)
	{
	
}

int main()
{
	
	return 0;
}
