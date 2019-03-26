#ifndef TRAX_H
#define TRAX_H
#include <iostream>
#include <string>
#include <sstream>

class trax
{
public:
    trax();
    virtual ~trax();

    virtual void Serialize();

private:

    enum e_dataTypes {
        dt_char = 0,
        dt_float,
        dt_quatfloat,
        dt_bool
    };

    const static int dataTypesNum = 4;
    const static int dataPacksFloat = 20;
    const static int dataPacksChar = 20;


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

    static const s_data_info dataInfo[dataPacksFloat];

    struct s_data_infochar
    {

        int type;
        std::string name;
        char data;
    };

    static const s_data_infochar dataInfochar[dataPacksChar];
};

#endif // TRAX_H
