#ifndef MEMENTOMORI_H
#define MEMENTOMORI_H
#include "using_libs.h"

namespace  Field{

    class Moment{
    public:
      virtual void WriteFile()=0;
      virtual void ReadFile()=0;
      virtual std::string date() = 0;
    };

    class CareTaker{
    public:
        virtual void BackUp()=0;
        virtual void Undo()=0;
    };
}

#endif // MEMENTOMORI_H
