#include "defs.h"
#include "library.h"
#include "functions.h"

void readMatrix(string s,vector<vf> &v1)
{
	vector<vf> res;
	fstream file;
	float f;
	file.open(s);

	string line;
	
	while(getline(file,line))
	{
		vf temp;
		stringstream ss(line);
		while(ss>>f)
			temp.pb(f);
		res.pb(temp);
	}

	int n=res.size();

	for(int i=0;i<n;i++)
	{
		vf temp;
		for(int j=0;j<n;j++)
			temp.push_back(res[j][i]);
		v1.push_back(temp);
	}
}

void readVector(string s,vf v1)
{
	fstream file;
	float f;
	file.open(s);

	string line;
	getline(file,line);
	
	vf temp;
	stringstream ss(line);
	while(ss>>f)
		v1.pb(f);

}

void help(string s)
{
	cout<<s<<endl;

	cout<<"input format :\n";

	cout<<"To call Convolution with padding \n";
	cout<<"convolution_withpadding_matrixmult padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows\n";
	cout<<"To call Convolution without padding \n";
	cout<<"convolution_withoutpadding_matrixmult padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows\n";

	cout<<"To call relu activation\n";
	cout<<"activation_relu matrix1.txt matrix1_numrows\n";

	cout<<"To call tanh activation\n";
	cout<<"activation_tanh matrix1.txt matrix1_numrows\n";

	cout<<"To do subsampling with maxpooling\n";
	cout<<"subsampling_maxpooling matrix1.txt matrix1_numrows padsize\n";

	cout<<"To do subsampling with average pooling\n";
	cout<<"subsampling_avgpooling matrix1.txt matrix1_numrows padsize\n";

	cout<<"To convert random float vector to probability vector using softmax\n";
	cout<<"probability_softmax matrix1.txt matrix1_numrows\n";

	cout<<"To convert random float vector to probability vector using sigmoid\n";
	cout<<"probability_sigmoid matrix1.txt matrix1_numrows\n";

}


int main(int argc, char** argv) 
{
	if(argc==7)
	{
		if(argv[1]=="convolution_withpadding_matrixmult")
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
			}

			vector<vf> v1;
			vector<vf> v2;
			readMatrix(argv[3],v1);

			if(v1.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(v1.size()!=n1)
			{
				help("Invalid Data");
				return 0;
			}
			readMatrix(argv[5],v2);

			if(v2.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}
			
			if(v2.size()!=n2)
			{
				help("Invalid Data");
				return 0;
			}

			// call function
		}
		else if(argv[1]=="convolution_withoutpadding_matrixmult")
		{
			int n1,n2,k;
			try
			{
				k=stoi(argv[2]);
				n1=stoi(argv[4]);
				n2=stoi(argv[6]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
			}

			vector<vf> v1;
			vector<vf> v2;
			readMatrix(argv[3],v1);

			if(v1.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(v1.size()!=n1)
			{
				help("Invalid Data");
				return 0;
			}
			readMatrix(argv[5],v2);

			if(v2.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}
			
			if(v2.size()!=n2)
			{
				help("Invalid Data");
				return 0;
			}
			//call function
		}
		else
			help("Invalid Format");
	}
	else if(argc==5)
	{
		if(argv[1]=="subsampling_maxpooling")
		{
			int n1,k;
			try{
				n1=stoi(argv[3]);
				k=stoi(argv[4]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
			}

			vector<vf> v1;
			readMatrix(argv[2],v1);

			if(v1.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(v1.size()!=n1)
			{
				help("Invalid Data");
				return 0;
			}

			//call max_pooling
		}
		else if(argv[1]=="subsampling_avgpooling")
		{
			int n1,k;
			try{
				n1=stoi(argv[3]);
				k=stoi(argv[4]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
			}

			vector<vf> v1;
			readMatrix(argv[2],v1);

			if(v1.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(v1.size()!=n1)
			{
				help("Invalid Data");
				return 0;
			}
			//call avg_pooling
		}
		else
			help("Invalid Format");
	}
	else if(argc==4)
	{
		if(argv[1]=="activation_relu")
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
			}

			vector<vf> v1;
			readMatrix(argv[2],v1);

			if(v1.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(v1.size()!=n1)
			{
				help("Invalid Data");
				return 0;
			}

			//call relu
		}
		else if(argv[1]=="activation_tanh")
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
			}

			vector<vf> v1;
			readMatrix(argv[2],v1);

			if(v1.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(v1.size()!=n1)
			{
				help("Invalid Data");
				return 0;
			}
			//call tanh
		}
		else if(argv[1]=="probability_sigmoid")
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
			}

			vf v1;
			readVector(argv[2],v1);

			if(v1.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}

			if(v1.size()!=n1)
			{
				help("Invalid Data");
				return 0;
			}
			//call sigmoid
		}
		else if(argv[1]=="probability_softmax")
		{
			int n1;
			try{
				n1=stoi(argv[3]);
			}catch(invalid_argument& e)
			{
				help("Invalid Argument");
			}

			vf v1;
			readVector(argv[2],v1);
			if(v1.size==0)
			{
				help("This File does not contain any data");
				return 0;
			}
			
			if(v1.size()!=n1)
			{
				help("Invalid Data");
				return 0;
			}
			//call softmax
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

