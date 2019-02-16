#include "defs.h"
#include "library.h"
#include "functions.h"
#include "leNet.h"

void print(vvf v)
{
	cout<<fixed<<setprecision(10);
	for(int i=0;i<v.size();++i)
	{
		for(int j=0;j<v[i].size();++j)
			cout<<v[i][j]<<"\t";
		cout<<"\n";
	}
}

void print(vf v)
{
	for(int i=0;i<v.size();++i)
		cout<<v[i]<<"\t";
	cout<<"\n";
}

int readMatrix(char* s, vvf &v1, int n, int columnMajor) //returns a corresponding error code for main functions
{
	if(n==0)
		return 2;
	vvf res;
	ifstream filein;
	float f;
	filein.open(s);

	string line;
	int j;
	while(filein>>f)
	{
		vf temp;
		temp.pb(f);
		j=1;
		while(j<n && filein>>f)
		{
			temp.pb(f);
			j++;
		}
		if(j<n)
			return 1;
		res.pb(temp);
		if(res.size()==n)
			break;
	}
	filein.close();
	if(res.size()==0)
		return 2;
	if(res.size()<n)
		return 1;

	for(int i=0;i<n;i++)
	{
		vf temp;

		for(int j=0;j<n;j++)
		{
			if(columnMajor)
				temp.pb(res[j][i]);
			else
				temp.pb(res[i][j]);
		}
		v1.pb(temp);
	}

	return 0;
}

int readVector(char* s, vf& v1, int n)
{
	if(n==0)
		return 2;
	ifstream fin;
	float f;
	fin.open(s);

	while(fin>>f)
	{
		v1.pb(f);
	}
	fin.close();
	if(v1.size()==0)
		return 2;

	if(v1.size()!=n)
		return 1;
	return 0;
}

void help(string s)
{
	cout<<s<<"\n\n";

	cout<<"input format : $ ./image (followed by the following\n\n";

	cout<<"To implement the LeNet Architecture\n";
	cout<<"\t normalised_image_data.txt conv1.txt conv2.txt fc1.txt fc2.txt\n";

	cout<<"To call Convolution with padding using matrix multiplication\n";
	cout<<"\tconvolution_withpadding_matrixmult padsize mode matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows\n";
	cout<<"To call Convolution without padding using matrix multiplication \n";
	cout<<"\tconvolution_withoutpadding_matrixmult mode matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows\n";

	cout<<"where mode is 1 for normal multiplication, 2 for pthread, 3 for OpenBLAS, 4 for MKL.\n";

	cout<<"To call Convolution with padding using convolution\n";
	cout<<"\tconvolution_withpadding_conv padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows\n";
	cout<<"To call Convolution without padding using convolution \n";
	cout<<"\tconvolution_withoutpadding_conv matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows\n";

	cout<<"To call relu activation\n";
	cout<<"\tactivation_relu matrix1.txt matrix1_numrows\n";

	cout<<"To call tanh activation\n";
	cout<<"\tactivation_tanh matrix1.txt matrix1_numrows\n";

	cout<<"To do subsampling with maxpooling\n";
	cout<<"\tsubsampling_maxpooling matrix1.txt matrix1_numrows\n";

	cout<<"To do subsampling with average pooling\n";
	cout<<"\tsubsampling_avgpooling matrix1.txt matrix1_numrows\n";

	cout<<"To convert random float vector to probability vector using softmax\n";
	cout<<"\tprobability_softmax matrix1.txt matrix1_numrows\n";

	cout<<"To convert random float vector to probability vector using sigmoid\n";
	cout<<"\tprobability_sigmoid matrix1.txt matrix1_numrows\n";

}


int main(int argc, char** argv) 
{
	int time;
	if(strcmp(argv[0],"time"))
		time=0;
	else
		time=1;
	
	if(argc==8+time)
	{
		if(!strcmp(argv[1+time],"convolution_withpadding_matrixmult"))
		{
			int k=atoi(argv[2+time]);
			int n1=atoi(argv[5+time]);
			int n2=atoi(argv[7+time]);
			int mode=atoi(argv[3+time]);

			if(k==0||n1==0||n2==0||mode<1||mode>4)
			{
				help("Invalid Argument");
				return 0;
			}

			vvf v1;
			vvf v2;
			int y=readMatrix(argv[4+time],v1,n1,1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}
			y=readMatrix(argv[6+time],v2,n2,1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}

			vvf res;
			conv_matrmult_pad(v1, v2, k, res, mode);
			print(res);
		}
		else
			help("Invalid Format");
	}

	else if(argc==7+time)
	{
		if(!strcmp(argv[1+time],"lenet"))
		{
			vvf image;
			vf prob;
			int y=readMatrix(argv[2+time],image,28,0);
			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}
			y=leNetArchitecture(image,argv[3+time],argv[4+time],argv[5+time],argv[6+time],prob);
			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}
			return 0;
		}

		else if(!strcmp(argv[1+time],"convolution_withpadding_conv")||!strcmp(argv[1+time],"convolution_withoutpadding_matrixmult"))
		{
			int k=atoi(argv[2+time]);
			int n1=atoi(argv[4+time]);
			int n2=atoi(argv[6+time]);

			if(k==0||n1==0||n2==0)
			{
				help("Invalid Argument");
				return 0;
			}

			if(!strcmp(argv[1+time],"convolution_withoutpadding_matrixmult")&&(k<1||k>4))
			{
				help("Invalid Argument");
				return 0;
			}

			vvf v1;
			vvf v2;
			int y=readMatrix(argv[3+time],v1,n1,1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}
			y=readMatrix(argv[5+time],v2,n2,1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}
			vvf res;
			if(!strcmp(argv[1+time],"convolution_withpadding_conv"))
				convolution_pad(v1, v2, k, res);
			else
				conv_matrmult_npad(v1,v2,res,k);
			
			// print(res);
		}
		else
			help("Invalid Format");
	}

	else if(argc==6+time)
	{
		if(!strcmp(argv[1+time],"convolution_withoutpadding_matrixmult")||!strcmp(argv[1+time],"convolution_withoutpadding_conv"))
		{
			int n1=atoi(argv[3+time]);
			int n2=atoi(argv[5+time]);
			
			if(n1==0||n2==0)
			{
				help("Invalid Argument");
				return 0;
			}

			vvf v1;
			vvf v2;
			int y=readMatrix(argv[2+time],v1,n1,1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}
			y=readMatrix(argv[4+time],v2,n2,1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}
			
			vvf res;
			if(!strcmp(argv[1+time],"convolution_withoutpadding_matrixmult"))
				conv_matrmult_npad(v1, v2, res, 1);
			else
				convolution_npad(v1, v2, res);
			print(res);
		}
		else
			help("Invalid Format");
	}

	else if(argc==4+time)
	{
		if(!strcmp(argv[1+time],"subsampling_maxpooling")||!strcmp(argv[1+time],"subsampling_avgpooling"))
		{
			int n1=atoi(argv[3+time]);;
			
			if(n1==0)
			{
				help("Invalid Argument");
				return 0;
			}

			vvf v1;
			int y=readMatrix(argv[2+time],v1,n1,1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}

			vvf res;
			if(!strcmp(argv[1+time],"subsampling_maxpooling"))
				maxPool(v1, res);
			else
				averagePool(v1, res);
			print(res);
		}

		else if(!strcmp(argv[1+time],"activation_relu")||!strcmp(argv[1+time],"activation_tanh"))
		{
			int n1=atoi(argv[3+time]);
			if(n1==0)
			{
				help("Invalid Argument");
				return 0;
			}

			vvf v1;
			int y=readMatrix(argv[2+time],v1,n1,1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}

			if(!strcmp(argv[1+time],"activation_relu"))
				relu(v1);
			else
				tanh(v1);
			print(v1);
		}
		
		else if(!strcmp(argv[1+time],"probability_sigmoid")||!strcmp(argv[1+time],"probability_softmax"))
		{
			int n1=atoi(argv[3+time]);
			if(n1==0)
			{
				help("Invalid Argument");
				return 0;
			}

			vf v1;
			int y=readVector(argv[2+time],v1,n1);

			if(y==2)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(y==1)
			{
				help("Invalid Data");
				return 0;
			}
			if(!strcmp(argv[1+time],"probability_sigmoid"))
				sigmoid(v1);
			else
				softmax(v1);
			print(v1);
		}
		
		else
			help("Invalid Format");
	}
	else
	{
		help("Invalid Format");
	}
	
	return 0;
}