g = g++ -c
head = defs.h library.h
obj = conv.o nonlactivation.o pooling.o probability.o
lib = -I /home/saurav/OpenBLAS/include/ -L/home/saurav/OpenBLAS/lib -lopenblas
files = main.cpp conv.cpp nonlactivation.cpp pooling.cpp probability.cpps

all: image

image: main.o $(obj) $(head)
	g++ -pthread -o image main.o $(obj) $(lib)

main.o: $(obj) functions.h $(head)
	$(g) main.cpp

conv.o: $(head)
	$(g) $(lib) conv.cpp

nonlactivation.o: $(head)
	$(g) nonlactivation.cpp

pooling.o: $(head)
	$(g) pooling.cpp

probability.o: $(head)
	$(g) probability.cpp

clean:
	rm image *.o