#include "gnuplot.h"

Gnuplot::Gnuplot()
{
    gnuplotpipe  = popen(GNUPLOT_NAME, "w");

    if (!gnuplotpipe)
    {
        cerr << ("Gnuplot not found !");
    }
}

Gnuplot::~Gnuplot()
{
    fprintf(gnuplotpipe,"exit\n");

    pclose(gnuplotpipe);
}

void Gnuplot::operator()(const string & command)
{
    fprintf(gnuplotpipe,"%s\n",command.c_str());
    fflush(gnuplotpipe); //без fflush ничего рисоваться не будет
}
