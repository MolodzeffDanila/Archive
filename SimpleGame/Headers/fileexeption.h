#ifndef FILEEXEPTION_H
#define FILEEXEPTION_H
#include <string>
#include <iostream>

class FileException{
private:
    std::string error;
public:
    FileException(std::string line){
        error = line;
        std::cout << line << std::endl;
    }
};

#endif // FILEEXEPTION_H
