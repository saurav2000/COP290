g = g++ -c
head = defs.h library.h
obj = matrixmkl.o conv.o nonlactivation.o pooling.o probability.o LeNet.o layer.o
OpenBLAS = -I /home/saurav/OpenBLAS/include/ -L/home/saurav/OpenBLAS/lib -lopenblas
files = main.cpp conv.cpp nonlactivation.cpp pooling.cpp probability.cpps
mkl =  -L~/intel/mkl/lib/intel64 -Wl,--no-as-needed -lpthread -lm -ldl -m64 -I ~/intel/mkl/include

all: image

image: main.o $(obj) $(head)
	g++ -pthread -o image main.o $(obj) $(OpenBLAS) $(mkl)

main.o: $(obj) functions.h leNet.h $(head)
	$(g) main.cpp

conv.o: $(head)
	$(g) $(OpenBLAS) conv.cpp

nonlactivation.o: $(head)
	$(g) nonlactivation.cpp

pooling.o: $(head)
	$(g) pooling.cpp

probability.o: $(head)
	$(g) probability.cpp

matrixmkl.o: $(head) 
	$(g) matrixmkl.cpp $(mkl)

LeNet.o: $(head) LeNetFunctions.h layer.o leNet.h
	$(g) LeNet.cpp

layer.o : $(head) pooling.o nonlactivation.o
	$(g) layer.cpp

clean:
	rm image *.o