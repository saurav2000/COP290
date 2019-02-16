#include "defs.h"
#include "functions.h"
#include "library.h"

void convolution_layer(vvvf &v1, vvvvf &k, vvvf &out)
{
	int k1=k.size(); //no. of output layers
	int k2=k[0].size(); //no. of input layers

	for(int i=0;i<k1;i++)
	{
		vvvf res;
		vvf fin;
		for(int j=0;j<k2;j++)
		{
			fin.clear();
			convolution_npad(v1[j],k[i][j],fin);
			res.pb(fin);
		}

		for(int a=0;a<fin.size();a++)
		{
			for(int b=0;b<fin[0].size();b++)
				fin[a][b]=0;
		}

		for(int a=0;a<k2;a++)
		{
			for(int b=0;b<res[0].size();b++)
			{
				for(int c=0;c<res[0][0].size();c++)
				{
					fin[b][c]+=(res[a][b][c]);
				}
			}
		}

		out.pb(fin);
	}
}

void maxsampling_layer(vvvf &v1, vvvf &out)
{
	vvf fin;
	for(int i=0;i<v1.size();i++)
	{
		fin.clear(); // to avoid using new memory each time anc clearing the old memory
		maxPool(v1[i],fin);
		out.pb(fin);
	}
}

void reluLayer(vvvf &v1)
{
	for(int i=0;i<v1.size();i++)
	{
		relu(v1[i]);
	}
}

void bias_add(vvvf &matrix, vf &bias)
{
	for(int i=0;i<matrix.size();++i)
	{
		for(int j=0;j<matrix[0].size();++j)
		{
			for(int k=0;k<matrix[0][0].size();++k)
				matrix[i][j][k]+=bias[i];
		}
	}
}

int readKernel(char* name, vvvvf &kern, vf &bias, int inputLayers, int outputLayers, int kernelSize)
{
	//opening the file
	float f;
	ifstream filein;
	filein.open(name);

	//temporary values to store the matrices
	vf x1;
	vvf x2;
	vvvf x3;

	for(int i=0;i<outputLayers;++i)
	{
		x3.clear(); //clearing everytime so that memory is not used
		for(int j=0;j<inputLayers;++j)
		{
			x2.clear();
			for(int k=0;k<kernelSize;++k)
			{
				x1.clear();
				for(int l=0;l<kernelSize;++l)
				{
					if(filein>>f)
						x1.pb(f);
					else if(!(i+j+k+l))
						return 2; //No data in file if all zeros
					else
						return 1; //Invalid data
				}
				x2.pb(x1);
			}
			x3.pb(x2);
		}
		kern.pb(x3);
	}

	for(int i=0;i<outputLayers;++i)
	{
		if(filein>>f)
			bias.pb(f);
		else
			return 1;
	}
	filein.close();
	return 0;
}