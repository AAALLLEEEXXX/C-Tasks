#ifndef PRESSURE_H
#define PRESSURE_H
#include <iostream>
#include <string>
#include <sstream>

class pressure
{
public:
    pressure();
    virtual ~pressure();

     virtual void Serialize();

private:
    enum e_dataTypes {
        dt_char = 0,
        dt_float,
        dt_quatfloat,
        dt_bool
    };

    const static int dataTypesNum = 4;
    const static int dataPacks = 20;


    struct s_data_type
    {
        int size;
        std::string name;
    };

    static const s_data_type typeInfo[dataTypesNum];

    struct s_data_info
    {

        int type;
        std::string name;
        float data;
    };

    static const s_data_info dataInfo[dataPacks];

};

#endif // PRESSURE_H
