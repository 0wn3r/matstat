#ifndef READCSV_H
#define READCSV_H

#include <string>
#include <vector>
#include <list>
#include "boost/filesystem/fstream.hpp"
#include <sstream>

struct datavalue
{
    double num;
    unsigned short set_number;
    float rank;
    unsigned short jonkir_count;
    bool operator < (const datavalue &a)
    {
        return num < a.num;
    }
};

class CSVReader
{
public:
    CSVReader(std::istream &m_str);
    CSVReader(std::istream &m_str, unsigned short globalCount);
    ~CSVReader();
    void ParseFile(std::istream &m_str);
    std::vector<std::list<datavalue>>const* getData() const {return vec;}
private:
    std::vector<std::list<datavalue>> *vec;
    unsigned short counter;
};

#endif // READCSV_H

