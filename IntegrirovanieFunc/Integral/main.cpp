#include <iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<stdlib.h>

using namespace std;

double IntegrRectLeft(std::vector<double>& x, std::vector<double>& y);
double IntegrRectRight(std::vector<double>& x, std::vector<double>& y);
double IntegrTrap(std::vector<double>& x, std::vector<double>& y);
double IntegrSimp(std::vector<double>& x, std::vector<double>& y);

int main()
{
    vector<double> x,y;
    for (float i = 0; i<=M_PI/2;i+=0.01)
    {//функция cos, на интервале [0,п/2]
        x.push_back(i);
        y.push_back(cos(i));
    }

    cout<<"Метод левых прямоугольников: "<<IntegrRectLeft(x,y)<<endl;
    cout<<"Метод правых прямоугольников: "<<IntegrRectRight(x,y)<<endl;
    cout<<"Метод трапеций: "<<IntegrTrap(x,y)<<endl;
    cout<<"Метод Симпсона: "<<IntegrSimp(x,y)<<endl;
    return 0;
}


double IntegrRectLeft(std::vector<double>& x, std::vector<double>& y)
{
    double summ = 0;
    for (int i = 0;i<x.size()-1;i++)
    {
        double delta = x[i+1]-x[i];
        double value = y[i+1];
        summ +=delta*value;
    }
    return  summ;
}

double IntegrRectRight(std::vector<double>& x, std::vector<double>& y)
{
    double summ = 0;
    for (int i = 0;i<x.size()-1;i++)
    {
        double delta = x[i+1]-x[i];
        double value = y[i];
        summ +=delta*value;
    }
    return  summ;
}

double IntegrTrap(std::vector<double>& x, std::vector<double>& y)
{
    double summ = 0;
    for (int i = 0;i<x.size()-1;i++)
    {
        double delta = x[i+1]-x[i];
        double value = (y[i+1]+y[i])/2;
        summ +=delta*value;
    }
    return  summ;
}

double IntegrSimp(std::vector<double>& x, std::vector<double>& y)
{
    double summ = 0;
    for (int i = 0;i<x.size()-2;i+=2)
    {
        double delta = (x[i+2]-x[i])/2;
        double value = (y[i+2]+4*y[i+1]+y[i])/3;
        summ +=delta*value;
    }
    if(x.size()%2 ==0)
    {
        summ+=(x[x.size()-1]-x[x.size()-2])*(y[y.size()-1]+y[y.size()-2])/2;
    }
    return  summ;
}
