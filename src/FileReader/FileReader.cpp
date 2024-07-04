#include "FileReader.hpp"

FileReader::FileReader()
{
    this->_name = "./Tests/Teste.txt" ;
    this->OpenRead();
    this->_file.close();
}

void FileReader::OpenRead()
{
    this->_file.open(this->_name, fstream::in);
    if(!this->_file.is_open())
    {
        cout << "Error ao abrir arquivo";
        exit(1);
    }
}

vector<string> FileReader::GetLines()
{
    vector<string> result;
    string line;
    this->OpenRead();

    while(getline(this->_file, line))
    {
        result.push_back(line);
    }
    this->_file.close();
    return result;
}
