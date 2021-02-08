#ifndef OBSERVER_H
#define OBSERVER_H
#define FILE_NAME_1 "logs_hero.txt"
#define FILE_NAME_2 "logs_cell.txt"
#include "Headers/using_libs.h"

namespace Logging{

class Subject;

    class Observer{
    public:
        virtual void update(Logging::Subject* hero)=0;
    };
}
#endif // OBSERVER_H
