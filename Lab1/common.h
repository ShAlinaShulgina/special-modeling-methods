#include <fstream>
#include <cmath>        // exp
#include <string.h>

#include "gnuplot.h"

class Common
{
private:

protected:
    FILE* file;
    std::string file_name;
    float x_0, x_n;
    float y_0;

    void getResult(float);

public:
    Common();
    ~Common();
    float dxdy(float x, float y);
    // works with file
    void openFile();
    void addDataOnFile(float x, float y);
    void closeFile();
    void draw();

    float h1, h2;
};
