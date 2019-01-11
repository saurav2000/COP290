#include "def.h"

vector<vf> relu(vector<vf> vec)
{
	int n=vec.size();
	int i,j;
	vector<vf> v1;

	for(i=0;i<n;i++)
	{
		vf temp;
		for(j=0;j<n;j++)
			temp.pb(max(0.0f,vec[i][j]));
		v1.pb(temp);
	}
	
	return v1;
}

vector<vf> tanh(vector<vf> vec)
{
	int n=vec.size();
	int i,j;
	vector<vf> v1;

	for(i=0;i<n;i++)
	{
		vf temp;
		for(j=0;j<n;j++)
		{
		    float x=vec[i][j];
			float y=(float)(1-exp(-2*x))/(exp(-2*x)+1);
			temp.pb(y);
		}
		v1.pb(temp);
	}
	
	return v1;
}
