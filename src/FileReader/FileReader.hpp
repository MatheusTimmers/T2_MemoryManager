#ifndef FILE_HPP
#define FILE_HPP
#include <fstream>

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class FileReader
{
    private:
        string _name;
        fstream _file;
        void OpenRead();


    public:
        FileReader();
        vector<string> GetLines();
};

#endif
