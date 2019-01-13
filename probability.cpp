#include "defs.h"
#include "library.h"

void sigmoid(vf &v)
{
	for(int i=0;i<v.size();++i)
		v[i]=1/(1+exp(-v[i]));
}

void softmax(vf &v)
{
	float sum=0.0f;

	for(int i=0;i<v.size();++i)
	{
		v[i]=exp(v[i]);
		sum+=v[i];
	}

	for(int i=0;i<v.size();++i)
		v[i]/=sum;
}
