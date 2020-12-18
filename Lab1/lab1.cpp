#include <iostream>
#include <iomanip>      // std::setw
#include <cmath>        // exp
#include <fstream>

#include <string.h>
#include <time.h>

using namespace std;

bool isCout;

float dxdy(float x, float y)
{
    return (exp(x) - 1);
}

FILE* openFile(std::string name)
{
    FILE* file = fopen(name.c_str(), "w");
    if (file == NULL)
    {
        perror("Error to open file");
        return NULL;
    }
    return file;
}

void addDataOnFile(FILE *f, float x, float y)
{
    fprintf(f,"%f\t%f\n", static_cast<double>(x), static_cast<double>(y));
}

void closeFile(FILE *f)
{
    fclose(f);
}

float Euler(float x_0, float y_0, float x_n, float h)
{
	string str = "Euler" + std::to_string(h) + ".dat";
    FILE *file = openFile(str);
    float x = x_0, y = y_0;
    float n = (x_n - x_0) / h;
    for (int i = 1; i <= n; i++)
    {
        x = x_0 + i * h;
        y = y + h * dxdy(x, y);
        addDataOnFile(file, x, y);
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    closeFile(file);
    return y;
}

float modifiedEuler(float x_0, float y_0, float x_n, float h)
{
	string str = "modifiedEuler" + std::to_string(h) + ".dat";
    FILE *file = openFile(str);
    float x = x_0, y = y_0, _x = x;
    float n = (x_n - x_0) / h;
    float _y;
    for (int i = 1; i <= n; i++)
    {
        _y = y + h * dxdy(x, y);
        x = x_0 + i * h;
        y = y + h / 2 * (dxdy(_x, y) + dxdy(x, _y));
        _x = x;
        addDataOnFile(file, x, y);
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    closeFile(file);
    return y;
}

float RK(float x_0, float y_0, float x_n, float h)
{
	string str = "RK" + std::to_string(h) + ".dat";
    FILE *file = openFile(str);
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
        addDataOnFile(file, x, y);
        if (::isCout) cout << "step=" << i <<
                " x=" << x << " y=" << y << endl;
    }
    closeFile(file);
    return y;
}

void call(float x_0, float y_0, float x_n, float h, string method_name, float(*foo) (float, float, float, float))
{
	clock_t currentTime;	
    cout << method_name << endl;
	//Берем текущее системное время
	currentTime = clock();
    cout << "h=" << h << " " << foo(x_0, y_0, x_n, h) << endl;
    //Берем разницу
	currentTime = clock() - currentTime;
	//Переводим в секунды
    cout << "Время работы: " << static_cast<double>(currentTime) / CLOCKS_PER_SEC << " s\n";
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

	call(x_0, y_0, x_n, h1, "Метод Эйлера", Euler);
	call(x_0, y_0, x_n, h2, "Метод Эйлера", Euler);
	call(x_0, y_0, x_n, h1, "Модифицированный метод Эйлера", modifiedEuler);
	call(x_0, y_0, x_n, h2, "Модифицированный метод Эйлера", modifiedEuler);
	call(x_0, y_0, x_n, h1, "Метода Рунге-Кутты 4 порядка", RK);
	call(x_0, y_0, x_n, h2, "Метода Рунге-Кутты 4 порядка", RK);

    return 0;
}
