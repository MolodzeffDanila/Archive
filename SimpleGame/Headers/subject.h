#ifndef SUBJECT_H
#define SUBJECT_H
#include "Headers/using_libs.h"
#include "Headers/observer.h"

namespace Logging {

class Bridge;

    class Subject{
    public:
        virtual void Subscribe(Logging::Bridge* abstr)=0;
        virtual void Unsubscribe(Logging::Bridge* abstr)=0;
        virtual void Notify()=0;
    };

    class Bridge{
    protected:
        Observer* observer;
    public:
        Bridge(Observer* observer){
            this->observer=observer;
        }
        virtual void Operation(Logging::Subject* sub){
            this->observer->update(sub);
        }
        virtual ~Bridge(){}
    };
}
#endif // SUBJECT_H
