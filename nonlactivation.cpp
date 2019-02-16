#include "defs.h"
#include "library.h"

void relu(vvf &vec)
{
	int n=vec.size();
	int i,j;
	vvf v1;

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			vec[i][j]=max(0.0f,vec[i][j]);
	}
}

void tanh(vvf &vec)
{
	int n=vec.size();
	int i,j;

	for(i=0;i<n;i++)
	{
		vf temp;
		for(j=0;j<n;j++)
		{
		    float x=vec[i][j];
			if(x>=0)
				vec[i][j]=(float)(1-exp(-2*x))/(exp(-2*x)+1);
			else
				vec[i][j]=(float)(-1+exp(2*x))/(exp(2*x)+1);
		}
	}
}
