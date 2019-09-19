#include <iostream>
#include <string>
#include <cmath>
#include <string>
using namespace std;

int main()
{
  setlocale(LC_ALL, "ru");

  string str;
  cout << "Введите строку: ";
  getline(cin, str);

  unsigned long length = str.size(); // длинна строки
  int number = 0;
  int n = 0;
  string iter;

  for (unsigned long i = 0; i < length; i++)
  {

       if (((str[i] >= 'A' && str[i] <='Z') && (str[i+1] >= 'A' && str[i+1] <='Z')) || ((str[i] >= 'A' && str[i] <='Z') && (str[i+1] == '\0')))
      {
       number++;
      }
      if(((str[i] >= 'A' && str[i] <='Z') && (str[i+1] >= '0' && str[i+1] <='9')) || ((str[i] >= '0' && str[i] <='9') && (str[i+1] >= '0' && str[i+1] <='9')))
      {
              iter +=str[i+1];
           //   cout<<"Iter: "<<iter<<endl;
      }
      if(((str[i] >= '0' && str[i] <='9') && (str[i+1] >= 'A' && str[i+1] <='Z')) || ((str[i] >= '0' && str[i] <='9') && ( str[i+1] == '\0')))
      {
          n = stoi(iter);
          number+=n;
          iter = "";
      }
   }

  cout<<number<<endl;
  return 0;
}
