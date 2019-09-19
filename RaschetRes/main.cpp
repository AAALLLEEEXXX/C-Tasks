#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include </usr/local/Eigen/Dense>
#include </usr/local/Eigen/LU>
#include <cmath>

using namespace std;

void show_vector( vector<int>&a)
{
        for (vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it)
                cout<<*it<<" ";
}

int main()
{
    setlocale(LC_ALL,"rus");
    std::vector<int> Z, T;

    cout<<"Z:"<<endl;
    Z.push_back(27);
    Z.push_back(31);
    Z.push_back(43);
    Z.push_back(58);
    Z.push_back(69);
    Z.push_back(86);
    Z.push_back(102);
    Z.push_back(111);
    Z.push_back(122);
    Z.push_back(137);
    Z.push_back(18);
    Z.push_back(176);
    show_vector(Z);
    cout<<"\n"<<endl;
    cout<<"T:"<<endl;
    T.push_back(71);
    T.push_back(64);
    T.push_back(52);
    T.push_back(41);
    T.push_back(33);
    T.push_back(23);
    T.push_back(17);
    T.push_back(12);
    T.push_back(2);
    T.push_back(0);
    T.push_back(87);
    T.push_back(-5);
    show_vector(T);
    cout<<"\n"<<endl;

    Eigen::MatrixXf G(T.size(), 2); //Создаем матрицу (Xi, 1)
    Eigen::VectorXf Y(Z.size());    //Создаем вектор (Yi)
    Eigen::Vector2f A;              //Вектор решения (K, log(K1)); Функция log(Z)=log(K1)+K*T;

    for (int i=0; i<G.rows(); i++)
    {
        G(i,0)=T[i];
        G(i,1)=1;
    }

    for (int i=0; i<Y.rows(); i++)
    {
        Y(i)=log10(Z[i]);
    }

    A=G.colPivHouseholderQr().solve(Y);

    float k, m;
    k=A(0);
    m=pow(10, A(1));
    cout<<"Решение:"<<endl;
    cout<<"k = "<<k<<endl<<"m = "<<m<<endl<<endl;
    cout<<"Z = "<<m<<" * 10^( "<<k<<" * T )"<<endl<<endl;

    Eigen::VectorXf R(Z.size()); //вектор для невязки
    Eigen::VectorXf M(Z.size());// вектор для модуля невязки
    Eigen::VectorXf P(Z.size()-1);

    for (int i=0; i<R.rows(); i++)
    {
        R(i)=m*pow(10, k*T[i]);
    }

    for (int i=0; i<R.rows(); i++)
     {
        R(i)=R(i)-Z[i]; //подсчитываем невязку
        M(i)=fabs(R(i));//модуль невязки
     }

    for (int i=0; i<Y.rows(); i++)
    {
        Y(i)=Z[i];
    }

float temp;
int q=Z.size();
for (int j=1;j<=q-1;j++)
for (int i=0;i<q-j;i++)
  if(M(i)>M(i+1))
   {//сортируем вектор модуля невязки
    temp=M(i+1);
    M(i+1)=M(i);
    M(i)=temp;
   };

float max;
int v;
  max=M(q-1);//находим максимальное значение невязки
  cout<<"Min value nevyzki: ";
  cout<<M(0)<<endl;//выводим наименьшее значение модуля невязки
  cout<<"Max value nevyzki: ";
  cout<<M(q-1)<<"\n"<<endl;//выводим наибольшее значение модуля невязки
  for (int i=0; i<q; i++)
  {
   if (max==R[i])
   {
    v=i;
   }
  }

 cout<<"Bad point Z:"<<Z[v]<<endl;
 cout<<"Bad point R:"<<R[v]<<"\n"<<endl;

for (int i = v; i <q; i++)
    {//записываем все хорошие эксперименты не включая эксперимент с большей невязкой
        Z[i] = Z[i+1];
    }

   Z[q]=0;

   for (int i = v; i <q; i++)
       {
           T[i] = T[i+1];
       }

      T[q]=0;

     for (int i=0;i<(q-1); i++)
    {
     P[i]=Z[i];
    }

     cout<<"Good experiment:"<<P.size()<<endl;

     for (int i=0;i<(q-1); i++)
    {
     cout<<P[i]<<endl;
    }
     cout<<"\n"<<endl;

 Eigen::VectorXf C(P.size());
    for (int i=0; i<P.size(); i++)
    {//находим все значения Z при хороших эксперементах
        C(i)=m*pow(10, k*T[i]);
    }

for (int i=0; i<C.rows(); i++)
{//находим невязки при хороших экспериментах
        C(i)=C(i)-P[i];
}

    cout<<"Качеcтво оценки = "<<R.norm()/Y.norm()<<endl<<endl;

    cout<<"Качеcтво новой оценки = "<<C.norm()/P.norm()<<endl<<endl;
}
