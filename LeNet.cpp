#include "library.h"
#include "LeNetFunctions.h"
#include "functions.h"
#include "defs.h"
#include "leNet.h"

void clearAll(vvvf &inp, vvvf &outp, vvvvf &kern, vf &bias)//used to clear all the matrices not to use extra space
{
	inp=outp;
	outp.clear();
	kern.clear();
	bias.clear();
}

void print(vvvf v1)
{
	cout<<"[";
	for(int i=0;i<v1.size();++i)
	{
		cout<<"[";
		for(int j=0;j<v1[0].size();++j)
		{
			cout<<"[";
			for(int k=0;k<v1[0][0].size();++k)
				cout<<v1[i][j][k]<<" ";
			cout<<"]\n";
		}
		cout<<"]\n";
	}
	cout<<"]\n";
}

//error code returned by file reading is the value returned here
int leNetArchitecture(vvf &img, char* c1, char* c2, char* fc1, char* fc2, vf &prob)
{
	vvvvf kernel;
	vf bias;
	vvvf input;
	vvvf output;
	input.pb(img);
	int errorCode;
	
	errorCode=readKernel(c1, kernel, bias, 1, 20, 5);
	if(errorCode==1 || errorCode==2)
		return errorCode;
	convolution_layer(input, kernel, output);
	bias_add(output, bias);
	clearAll(input,output,kernel,bias);

	maxsampling_layer(input,output);
	clearAll(input,output,kernel,bias);


	errorCode=readKernel(c2, kernel, bias, 20, 50, 5);
	if(errorCode==1 || errorCode==2)
		return errorCode;
	convolution_layer(input, kernel, output);
	bias_add(output, bias);
	clearAll(input,output,kernel,bias);


	maxsampling_layer(input,output);
	clearAll(input,output,kernel,bias);

	errorCode=readKernel(fc1, kernel, bias, 50, 500, 4);
	if(errorCode==1 || errorCode==2)
		return errorCode;
	convolution_layer(input, kernel, output);
	bias_add(output, bias);
	reluLayer(output);
	clearAll(input,output,kernel,bias);

	errorCode=readKernel(fc2, kernel, bias, 500, 10, 1);
	if(errorCode==1 || errorCode==2)
		return errorCode;
	convolution_layer(input, kernel, output);
	bias_add(output, bias);

	for(int i=0;i<output.size();++i)
		prob.pb(output[i][0][0]);


	softmax(prob);
	
	vector<pair<float,int> > vect;
	for (int i = 0; i < 10; ++i)
		vect.pb(mp(prob[i],i));
	
	sort(vect.rbegin(), vect.rend());

	for(auto i=0;i<10;++i)
		cout<<"The probability of digit "<< vect[i].second << "is "<< vect[i].first<<"\n";
	
	return 0;
}