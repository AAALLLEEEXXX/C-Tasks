#include "trax.h"
#include <iostream>
#include <QFile>
#include <QTextStream>


trax::trax()
{

}

trax::~trax(){

}

const trax::s_data_type trax::typeInfo[] =
{
    {1, "char"},
    {4, "float"},
    {16, "quatfloat"},
    {1, "bool"}
};

const trax::s_data_info trax::dataInfo[] =
{
    {dt_float,"kHeading", 141.032f},
    {dt_float, "kPitch", 1.13858f},
    {dt_float, "kRoll", 0.436141f},
    {dt_float, "kAccelX", -0.0200237f},
    {dt_float, "kAccelY", 0.00766917f},
    {dt_float, "kAccelZ", 1.00748f},
    {dt_float, "kMagX", -14.9151f},
    {dt_float, "kMagY", -10.8245f},
    {dt_float, "kMagZ", 52.3099f},
    {dt_float, "kGyroX", 0},
    {dt_float, "kGyroY", 0},
    {dt_float, "kGyroZ", 0}
};

const trax::s_data_infochar trax::dataInfochar[] =
{

    {dt_char, "kHeadingStatus", 'N'},

};

void trax::Serialize()
{

    QString str;

    QFile file("/Users/aleksej/Desktop/sensors.log");
    QFile fileOut("/Users/aleksej/Desktop/sensors.log"); // Связываем объект с файлом sensors.log
        if(fileOut.open(QIODevice::Append | QIODevice::Text))
        { // Если файл успешно открыт для записи в текстовом режиме
            QTextStream writeStream(&fileOut); // Создаем объект класса QTextStream
    // и передаем ему адрес объекта fileOut
            writeStream << "kHeading: " + str.setNum(dataInfo[0].data) + "\n"; // Посылаем строку в поток для записи
            writeStream << "kPitch: "+ str.setNum(dataInfo[1].data) + "\n";
            writeStream << "kRoll: "+ str.setNum(dataInfo[2].data) + "\n";
            writeStream << "kHeadingStatus: "+ str.setNum(dataInfochar[0].data) + "\n";
            writeStream << "kAccelX: "+ str.setNum(dataInfo[3].data) + "\n";
            writeStream << "kAccelY: "+ str.setNum(dataInfo[4].data) + "\n";
            writeStream << "kAccelZ: "+ str.setNum(dataInfo[5].data) + "\n";
            writeStream << "kMagX: "+ str.setNum(dataInfo[6].data) + "\n";
            writeStream << "kMagY: "+ str.setNum(dataInfo[7].data) + "\n";
            writeStream << "kMagZ: "+ str.setNum(dataInfo[8].data) + "\n";
            writeStream << "kGyroX: "+ str.setNum(dataInfo[9].data) + "\n";
            writeStream << "kGyroY: "+ str.setNum(dataInfo[10].data) + "\n";
            writeStream << "kGyroZ: "+ str.setNum(dataInfo[11].data) + "\n";
            writeStream << "=============================== Trax sensor data\n";
            fileOut.close(); // Закрываем файл
        }
}
