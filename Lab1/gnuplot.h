// gnuplot.h
#ifndef _GNUPLOT_H_
#define _GNUPLOT_H_

#include <cstdio>
#include <string>
#include <iostream>

#define GNUPLOT_NAME "gnuplot -persist"

using std::string;
using std::cerr;

class Gnuplot
{
public:
    Gnuplot();
    ~Gnuplot();
    void operator ()(const string & command); // отправить команду gnuplot

protected:
    FILE *gnuplotpipe;
};

#endif // #ifndef _GNUPLOT_H_
