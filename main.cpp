#include "defs.h"
#include "library.h"

int main(int argc, char** argv) 
{
	if(argc==6)
	{
		if(argv[1]=="convolution_withpadding_matrixmult")
		{
			//call function
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
