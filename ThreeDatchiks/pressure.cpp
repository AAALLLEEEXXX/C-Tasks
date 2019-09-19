#include "pressure.h"
#include <iostream>
#include <QFile>
#include <QTextStream>

pressure::pressure()
{

}

pressure::~pressure(){

}

const pressure::s_data_type pressure::typeInfo[] =
{
    {2, "float"},
};

const pressure::s_data_info pressure::dataInfo[] =
{
    {dt_float,"Pressure", 98.1f},
    {dt_float, "Temperature", 28.4f},
};

void pressure::Serialize()
{
    QString str;

    QFile file("/Users/aleksej/Desktop/sensors.log");
    QFile fileOut("/Users/aleksej/Desktop/sensors.log"); // Связываем объект с файлом sensors.log
        if(fileOut.open(QIODevice::Append | QIODevice::Text))
        { // Если файл успешно открыт для записи в текстовом режиме
            QTextStream writeStream(&fileOut); // Создаем объект класса QTextStream
    // и передаем ему адрес объекта fileOut
            writeStream << "Pressure: " + str.setNum(dataInfo[0].data) + "\n"; // Посылаем строку в поток для записи
            writeStream << "Temperature: " + str.setNum(dataInfo[1].data) + "\n";
            writeStream << "=============================== Pressure sensor data\n";
            fileOut.close(); // Закрываем файл
        }
}
