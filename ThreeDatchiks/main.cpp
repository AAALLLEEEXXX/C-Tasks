#include <iostream>
#include "trax.h"
#include "pressure.h"
#include "dus.h"
#include <QFile>
#include <QTextStream>

using namespace std;

int main()
{
    int number;
    trax Traxv;
    pressure Pres;
    dus Dus;

    for(int i = 0; i<10;){
        cout << "Выберите тип датчика:" << endl;
        cout << "1 - TRAX" << endl;
        cout << "2 - Pressure" << endl;
        cout << "3 - DUS" << endl;
        cout << "4 - Очистить файл sensors.log" << endl;
        cin >> number;

    switch (number) {
    case 1:
     Traxv.Serialize();
     cout << "Данные датчика TRAX записаны в файл sensors.log" << endl;
     i++;
     cout << "Всего итераций: 10. Осталось: "<< 10 - i << endl;
        break;
    case 2:
     Pres.Serialize();
     cout << "Данные датчика Pressure записаны в файл sensors.log" << endl;
     i++;
     cout << "Всего итераций: 10. Осталось: "<< 10 - i << endl;
        break;
    case 3:
     Dus.Serialize();
     cout << "Данные датчика DUS записаны в файл sensors.log" << endl;
     i++;
     cout << "Всего итераций: 10. Осталось: "<< 10 - i << endl;
        break;
    case 4:
     Dus.Clean();
        break;
    default:
        cout << "Ошибка. Попробуйте снова выбрать датчик." << endl;
        break;
    }
    }
    return 0;
}
