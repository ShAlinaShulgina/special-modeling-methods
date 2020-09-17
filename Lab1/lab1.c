#include <iostream>
#include <iomanip>      // std::setw
#include <cmath>        // exp
#include <string.h>

using namespace std;

bool isCout;

float dxdy(float x, float y)
{
    return (exp(x) - 1);
}

float Euler(float x_0, float y_0, float x_n, float h)
{
    float x = x_0, y = y_0;
    float n = (x_n - x_0) / h;
    for (int i = 1; i <= n; i++)
    {
        x = x_0 + i * h;
        y = y + h * dxdy(x, y);
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    return y;
}

float modifiedEuler(float x_0, float y_0, float x_n, float h)
{
    float x = x_0, y = y_0, _x = x;
    float n = (x_n - x_0) / h;
    float _y;
    for (int i = 1; i <= n; i++)
    {
        _y = y + h * dxdy(x, y);
        x = x_0 + i * h;
        y = y + h / 2 * (dxdy(_x, y) + dxdy(x, _y));
        _x = x;
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    return y;
}

float RK(float x_0, float y_0, float x_n, float h)
{
    float k1 = 0.f, k2 = 0.f, k3 = 0.f, k4 = 0.f;
    float x = x_0, y = y_0;
    float n = (x_n - x_0) / h;
    for (int i = 1; i <= n; i++)
    {
        k1 = dxdy(x, y);
        k2 = dxdy(x + h * 0.5f, y + h * k1 * 0.5f);
        k3 = dxdy(x + h * 0.5f, y + h * k2 * 0.5f);
        k4 = dxdy(x + h, y + h * k3);

        y = y + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        x = x_0 + i * h;
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    return y;
}

int main(int argc, char *argv[])
{
    float h1 = 0.01f, h2 = 0.001f;
    float x_0 = 0, x_n = 1;
    float y_0 = 0;

    if (argc > 1)
    {
        if (!(strcmp(argv[1], "-1")))
            ::isCout = true;
        else
            ::isCout = false;
    }
    else
        ::isCout = false;

    cout << "Метод Эйлера \nh=" << h1 << " " << Euler(x_0, y_0, x_n, h1) << "\nh=" << h2 << " " << Euler(x_0, y_0, x_n, h2) << endl;

    cout << "Модифицированный метод Эйлера \nh=" << h1 << " " << modifiedEuler(x_0, y_0, x_n, h1) << "\nh=" << h2 << " " << modifiedEuler(x_0, y_0, x_n, h2) << endl;

    cout << "Метода Рунге-Кутты четвертого порядка \nh=" << h1 << " " << RK(x_0, y_0, x_n, h1) << "\nh=" << h2 << " " << RK(x_0, y_0, x_n, h2) << endl;
    
    return 0;
}
