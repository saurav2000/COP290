#include "defs.h"

vf sigmoid(vf v)
{
	vf res;
	for(int i=0;i<v.size();++i)
	{
		float f = exp(-v[i]);
		res.pb(1/(1+f));
	}
	return res;
}

vf softmax(vf v)
{
	vf res;
	float sum=0.0f;
	for(int i=0;i<v.size();++i)
	{
		float f=exp(v[i]);
		sum+=f;
		res.pb(f);
	}

	for(int i=0;i<res.size();++i)
		res[i]/=sum;

	return res;
}
