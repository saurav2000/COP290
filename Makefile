g = g++ -c
head = defs.h library.h
obj = conv.o nonlactivation.o pooling.o probability.o

all: image

image: main.o $(obj)
	g++ -o image main.o $(obj)

main.o: $(obj) functions.h $(head)
	$(g) main.cpp

conv.o: $(head)
	$(g) conv.cpp

nonlactivation.o: $(head)
	$(g) nonlactivation.cpp

pooling.o: $(head)
	$(g) pooling.cpp

probability.o: $(head)
	$(g) probability.cpp

clean:
	rm image *.o