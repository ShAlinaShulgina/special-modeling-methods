all : lab1

lab1: lab1.o common.o gnuplot.o
	g++ lab1.o common.o gnuplot.o -o lab1

lab1.o: lab1.cpp
	g++ -c lab1.cpp

common.o : common.cpp
	g++ -c common.cpp

gnuplot.o : gnuplot.cpp
	g++ -c gnuplot.cpp

clean:
	rm -rf *.o lab1
