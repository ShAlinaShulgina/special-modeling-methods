#include "common.h"

using namespace std;

bool isCout;

class Euler : public Common
{
public:
    Euler();
    void getResult(float);
};

class ModEuler : public Common
{
public:
    ModEuler();
    void getResult(float);
};

class RK: public Common
{
public:
    RK();
    void getResult(float);
};

Euler::Euler()
{
    file_name = "Euler.dat";
    openFile();
}

void Euler::getResult(float h)
{
    float x = x_0, y = y_0;
    float n = (x_n - x_0) / h;
    for (int i = 1; i <= n; i++)
    {
        x = x_0 + i * h;
        y = y + h * dxdy(x, y);
        addDataOnFile(x, y);
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    closeFile();
    cout << y << endl;
}

ModEuler::ModEuler()
{
    file_name = "modifiedEuler.dat";
    openFile();
}

void ModEuler::getResult(float h)
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
        addDataOnFile(x, y);
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    closeFile();
    cout << y << endl;
}

RK::RK()
{
    file_name = "RK.dat";
    openFile();
}

void RK::getResult(float h)
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
        addDataOnFile(x, y);
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    closeFile();
    cout << y << endl;
}


int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (!(strcmp(argv[2], "-1")))
            ::isCout = true;
        else
            ::isCout = false;
        if (!(strcmp(argv[1], "-e")))
        {
            cout << "Метод Эйлера" << endl;
            Euler* euler = new Euler();
            euler->getResult(euler->h1);
            euler->draw();
            euler->getResult(euler->h2);
            euler->draw();
            std::cin.get();
        }
        else if (!(strcmp(argv[1], "-me")))
        {
            cout << "Модифицированный метод Эйлера" << endl;
            ModEuler *meuler = new ModEuler();
            meuler->getResult(meuler->h1);
            meuler->draw();
            meuler->getResult(meuler->h2);
            meuler->draw();
            std::cin.get();
        }
        else if (!(strcmp(argv[1], "-rk")))
        {
            cout << "Метода Рунге-Кутты четвертого порядка" << endl;
            RK *rk = new RK();
            rk->getResult(rk->h1);
            rk->draw();
            rk->getResult(rk->h2);
            rk->draw();
            std::cin.get();
        }
        else
        {
            cout << "Wasn't choose method" << endl;
        }
    }
    else
       ::isCout = false;
    return 0;
}
