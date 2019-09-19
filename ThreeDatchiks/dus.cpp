#include "dus.h"
#include <iostream>
#include <QFile>
#include <QTextStream>

dus::dus()
{

}

dus::~dus(){

}

const dus::s_data_type dus::typeInfo[] =
{
    {1, "char"},
    {4, "float"},
    {16, "unsigned short"},
};

const dus::s_data_info dus::dataInfo[] =
{

    {dt_float, "W_x"},
    {dt_float, "W_y"},
    {dt_float, "W_z"},
    {dt_float, "A_x"},
    {dt_float, "A_y"},
    {dt_float, "A_z"},
};

const dus::s_data_infochar dus::dataInfochar[] =
{

    {dt_char, "status", 'N'},

};

const dus::s_data_infounshort dus::dataInfoShort[] =
{

    {dt_unsignedshort, "temperature", 13},

};

void dus::Serialize()
{
    QString str;

    QFile file("/Users/aleksej/Desktop/sensors.log");
    QFile fileOut("/Users/aleksej/Desktop/sensors.log"); // Связываем объект с файлом sensors.log
        if(fileOut.open(QIODevice::Append | QIODevice::Text))
        { // Если файл успешно открыт для записи в текстовом режиме
            QTextStream writeStream(&fileOut); // Создаем объект класса QTextStream
    // и передаем ему адрес объекта fileOut
            writeStream << "status: " + str.setNum(dataInfochar[0].data) + "\n"; // Посылаем строку в поток для записи
            writeStream << "temperature: " + str.setNum(dataInfoShort[0].data) + "\n";
            writeStream << "W_x: " + str.setNum(dataInfo[0].data) + "\n"; // Посылаем строку в поток для записи
            writeStream << "W_y: " + str.setNum(dataInfo[1].data) + "\n";
            writeStream << "W_z: " + str.setNum(dataInfo[2].data) + "\n"; // Посылаем строку в поток для записи
            writeStream << "A_x: " + str.setNum(dataInfo[3].data) + "\n";
            writeStream << "A_y: " + str.setNum(dataInfo[4].data) + "\n"; // Посылаем строку в поток для записи
            writeStream << "A_z: " + str.setNum(dataInfo[5].data) + "\n";
            writeStream << "=============================== DUS sensor data\n";
            fileOut.close(); // Закрываем файл
        }
}

void dus::Clean()
{
    QFile file("/Users/aleksej/Desktop/sensors.log");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
      file.close();
}
