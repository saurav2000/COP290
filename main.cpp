#include "defs.h"
#include "library.h"
#include "functions.h"

vector<vf> readMatrix(string s)
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

	return res;
}

void help(string s)
{

}


int main(int argc, char** argv) 
{
	if(argc==6)
	{
		if(argv[1]=="convolution_withpadding_matrixmult")
		{
			call function
		}
		else
		{
			//call help()
		}
	}
	else if(argc==3)
	{
		if(argv[1]=="activation_relu")
		{
			//call relu
		}
		else if(argv[1]=="activation_tanh")
		{
			//call tanh
		}
		else if(argv[1]=="subsampling_maxpooling")
		{
			//call max_pooling
		}
		else if(argv[1]=="subsampling_avgpooling")
		{
			//call avg_pooling
		}
		else if(argv[1]=="probability_sigmoid")
		{
			//call sigmoid
		}
		else if(argv[1]=="probability_softmax")
		{
			//call softmax
		}
		else
		{
			//call help()
		}
	}
	else
	{
		//call help()
	}
	return 0;
}
