#include "common.h"

Common::Common()
{
    h1 = 0.01f;
    h2 = 0.001f;
    x_0 = 0;
    x_n = 1;
    y_0 = 0;
}

Common::~Common()
{
}

void Common::openFile()
{
    file = fopen(file_name.c_str(), "w");
    if (file == NULL)
    {
        perror("Error to open file");
        return;
    }
}

void Common::addDataOnFile(float x, float y)
{
    if (file == NULL)
        return;
    fprintf(file,"%f\t%f\n", static_cast<double>(x), static_cast<double>(y));
}

void Common::closeFile()
{
    if (file == NULL)
        return;
    fclose(file);
}

float Common::dxdy(float x, float y)
{
    return (exp(x) - 1);
}

void Common::draw()
{
    Gnuplot plot;
    std::string out;
    plot("set xrange [0:1]");
    plot("set yrange [0:1]");
    out = "plot'" + file_name + "' with lines ls 123";
    plot(out.c_str());
}
