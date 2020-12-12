/* 
 * Решение уравнения Вольтера 2 рода методами:
 * трапеций,
 * Симпсона,
 * 3/8
 * 6 вариант
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include <cstring> // memset
#include <cmath>

using namespace std;

double k(double x, double s)
{
	return ((2 + cos(x)) / (2 + cos(s)));
}

double f(float x)
{
	return exp(x) * sin(x);
}

double test_u(double x)
{
    return exp(x) * ( sin(x) + (2 + cos(x)) * log(3 / (2 + cos(x))));
}

double trapezeCoef(int j, int k)
{
    if (j == 0 || j == k)
        return 1;
    else
        return 2;
}
        
double trapeze(double *s, int idx, double h, double *u)
{
    double sum = 0;
    for (int i = 0; i < idx; i++)
    {
        sum += trapezeCoef(i, idx) * k(s[idx], s[i]) * u[i];
    }
    return (f(s[idx]) + h / 2 * sum) / (1 - h / 2 * k(s[idx], s[idx]));
}

double simpson(double *s, int idx, double h, double *u)
{
    double sum = 0;
    double sum1 = 0;
    for (int i = 1; i < (int)((idx / 2) + 1); i++)
    {
        sum += 4 * k(s[idx], s[2 * i - 1]) * u[2 * i - 1];
    }
    for (int i = 1; i < (int)(idx / 2); i++)
    {
        sum1 += 2 * k(s[idx], s[2 * i]) * u[2 * i];
    }
    return f(s[idx]) + h / 3 * (k(s[idx], s[0]) * u[0] + sum + sum1) / (1 - h / 3 * k(s[idx], s[idx]));
}

double three_eights(double *s, int idx, double h, double *u)
{
    double sum = 0;
    double sum1 = 0;
    for (int i = 1; i < (int)(idx / 3 + 1); i++)
    {
        sum += 3 * (k(s[idx], s[3 * i - 2]) * u[3 * i - 2] + k(s[idx], s[3 * i - 1]) * u[3 * i - 1]);
    }
    for (int i = 1; i < (int)(idx / 3); i++)
    {
        sum1 += 2 * k(s[idx], s[3 * i]) * u[3 * i];
    }
    return f(s[idx]) + 3 * h / 8 * (k(s[idx], s[0]) * u[0] + sum + sum1) / (1 - 3 * h / 8 * k(s[idx], s[idx]));
}

void printMass(double *mass, int n)
{
	for(int i = 0; i < n; i++)
		cout << setw(8) << mass[i] << " ";
	cout << endl;
}

void fprintMass(string f_name, string method, double *mass, int n)
{
	ofstream file(f_name, ios_base::app);
	if (!file)
	{
		cout << "Error open file" << endl;
		return;
	}
	file << method << endl;
	for(int i = 0; i < n; i++)
		file << mass[i] << endl;
	file.close();
}

void solution(double a, double b, int n, string file = "")
{
	double h = (b - a) / n; // step
	double x[n + 1];
	for(int i = 0; i < n + 1; i++)
		x[i] = a + i * h;
	cout << "X" << endl;
	printMass(x, n + 1);
	if (!file.empty())
		fprintMass(file, "X", x, n + 1);
	
	// Метод трапеций
	double u[n + 1];
	memset(u, 0, sizeof(u));
	u[0] = f(x[0]);
	for(int i = 1; i < n + 1; i++)
	    u[i] = trapeze(x, i, h, u);
	cout << "Метод трапеций" << endl;
	printMass(u, n + 1);
	if (!file.empty())
		fprintMass(file, "Трапеций", u, n + 1);
	
	//Симпсон
	memset(u, 0, sizeof(u));
	u[0] = f(x[0]);
	for(int i = 1; i < n + 1; i++)
	    u[i] = simpson(x, i, h, u);
	cout << "Метод Симпсона" << endl;
	printMass(u, n + 1);
	if (!file.empty())
		fprintMass(file, "Симпсон", u, n + 1);
	
	
	//3/8
	memset(u, 0, sizeof(u));
	u[0] = f(x[0]);
	for(int i = 1; i < n + 1; i++)
	    u[i] = three_eights(x, i, h, u);
	cout << "Метод трех восьмых" << endl;
	printMass(u, n + 1);
	if (!file.empty())
		fprintMass(file, "Трех восьмых", u, n + 1);
	
	
	// Аналитическое
	memset(u, 0, sizeof(u));
	for(int i = 0; i < n + 1; i++)
	    u[i] = test_u(x[i]);
	cout << "Аналитическое решение" << endl;
	printMass(u, n + 1);
	if (!file.empty())
		fprintMass(file, "Аналитическое решение", u, n + 1);
}

int main() 
{
	double a = 0;
	double b = 2;
	// решить для 10 и для 100 узлов
	solution(a, b, 10, "Volter_10.dat");
	solution(a, b, 100, "Volter_100.dat");
	return 0;
}
