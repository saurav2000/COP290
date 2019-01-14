#include "defs.h"
#include "library.h"
#include "functions.h"

void print(vector<vf> v)
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

int readMatrix(string s,vector<vf> &v1,int n)
{
	if(n==0)
		return 2;
	vector<vf> res;
	ifstream filein;
	float f;
	filein.open(s);

	string line;
	int j;
	while(filein>>f)
	{
		vf temp;
		temp.push_back(f);
		j=1;
		while(j<n && filein>>f)
		{
			temp.pb(f);
			j++;
		}
		if(j<n)
			return 1;
		res.pb(temp);
	}
	filein.close();
	if(res.size()==0)
		return 2;
	if(res.size()<n)
		return 1;

	for(int i=0;i<res.size();i++)
	{
		vf temp;

		for(int j=0;j<n;j++)
			temp.push_back(res[j][i]);
		v1.push_back(temp);
	}

	return 0;
}

int readVector(string s,vf& v1,int n)
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

	cout<<"To call Convolution with padding using matrix multiplication\n";
	cout<<"\tconvolution_withpadding_matrixmult padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows\n";
	cout<<"To call Convolution without padding using matrix multiplication \n";
	cout<<"\tconvolution_withoutpadding_matrixmult matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows\n";

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
	if(argc==7)
	{
		if(!strcmp(argv[1],"convolution_withpadding_matrixmult")||!!strcmp(argv[1],"convolution_withpadding_conv"))
		{
			int n1,n2,k;
			try{
				k=stoi(argv[2]);
				n1=stoi(argv[4]);
				n2=stoi(argv[6]);
			}
			catch(invalid_argument& e)
			{
				help("Invalid Argument");
				return 0;
			}

			vector<vf> v1;
			vector<vf> v2;
			int y=readMatrix(argv[3],v1,n1);

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
			y=readMatrix(argv[5],v2,n2);

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

			vector<vf> res;
			if(!strcmp(argv[1],"convolution_withpadding_matrixmult"))
				conv_matrmult_pad(v1, v2, k, res);
			else
				convolution_pad(v1, v2, k, res);
			print(res);
		}
		else
			help("Invalid Format");
	}

	else if(argc==6)
	{
		if(!strcmp(argv[1],"convolution_withoutpadding_matrixmult")||!strcmp(argv[1],"convolution_withoutpadding_conv"))
		{
			int n1,n2;
			try
			{
				n1=stoi(argv[3]);
				n2=stoi(argv[5]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
				return 0;
			}

			vector<vf> v1;
			vector<vf> v2;
			int y=readMatrix(argv[2],v1,n1);

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
			y=readMatrix(argv[4],v2,n2);

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
			
			vector<vf> res;
			if(!strcmp(argv[1],"convolution_withoutpadding_matrixmult"))
				conv_matrmult_npad(v1, v2, res);
			else
				convolution_npad(v1, v2, res);
			print(res);
		}
		else
			help("Invalid Format");
	}

	else if(argc==4)
	{
		if(!strcmp(argv[1],"subsampling_maxpooling"))
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
				return 0;
			}

			vector<vf> v1;
			int y=readMatrix(argv[2],v1,n1);

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

			vector<vf> res;
			maxPool(v1, res);
			print(res);
		}
		else if(!strcmp(argv[1],"subsampling_avgpooling"))
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
				return 0;
			}

			vector<vf> v1;
			int y=readMatrix(argv[2],v1,n1);

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
			
			vector<vf> res;
			averagePool(v1, res);
			print(res);
		}

		else if(!strcmp(argv[1],"activation_relu"))
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
				return 0;
			}

			vector<vf> v1;
			int y=readMatrix(argv[2],v1,n1);

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

			relu(v1);
			print(v1);
		}
		else if(!strcmp(argv[1],"activation_tanh"))
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
				return 0;
			}

			vector<vf> v1;
			int y=readMatrix(argv[2],v1,n1);

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
			
			tanh(v1);
			print(v1);
		}
		else if(!strcmp(argv[1],"probability_sigmoid"))
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
				return 0;
			}

			vf v1;
			int y=readVector(argv[2],v1,n1);

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
			
			sigmoid(v1);
			print(v1);
		}
		else if(!strcmp(argv[1],"probability_softmax"))
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
				return 0;
			}

			vf v1;
			int y=readVector(argv[2],v1,n1);
			
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

