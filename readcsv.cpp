#include "readcsv.h"
CSVReader::CSVReader(std::istream &str)
{
    vec = new std::vector<std::list<datavalue>>;
    counter = 0;
    ParseFile(str);
}

CSVReader::CSVReader(std::istream &str, unsigned short globalCount)
{
    vec = new std::vector<std::list<datavalue>>;
    counter = globalCount;
    ParseFile(str);
}

CSVReader::~CSVReader()
{
    delete vec;
}

void CSVReader::ParseFile(std::istream &m_str)
{
    std::string line;
    std::list<datavalue> templist;
    while (getline(m_str, line))
    {
        std::stringstream lineStream(line);
        std::string data;
        templist.clear();
        while (getline(lineStream, data, ';'))
        {
            templist.push_back({std::stod(data), counter, 0, 0});
        }
        vec->push_back(templist);
        counter++;
    }
}
