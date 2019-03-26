#ifndef DUS_H
#define DUS_H
#include <iostream>
#include <string>
#include <sstream>

class dus
{
public:
    dus();
    virtual ~dus();

     virtual void Serialize();
    virtual void Clean();

private:
    enum e_dataTypes {
        dt_char = 0,
        dt_float,
        dt_unsignedshort,
        dt_bool
    };

    const static int dataTypesNum = 4;
    const static int dataPacks = 20;
    const static int dataPacksChar = 20;
    const static int dataUnShort = 20;

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

    struct s_data_infochar
    {

        int type;
        std::string name;
        char data;
    };

    static const s_data_infochar dataInfochar[dataPacksChar];

    struct s_data_infounshort
    {

        int type;
        std::string name;
        unsigned short data;
    };

    static const s_data_infounshort dataInfoShort[dataPacksChar];
};

#endif // DUS_H
