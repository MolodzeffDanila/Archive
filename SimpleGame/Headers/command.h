#ifndef COMMAND_H
#define COMMAND_H
#include "Headers/hero.h"
namespace  Command{

    class Command{
    public:
        virtual void Execute(Unit::Hero *const iter) = 0;
        virtual ~Command(){}
    };

    class LeftCommand : public Command{
    public:
        void Execute(Unit::Hero* iter)override{
            iter -> Step_Left();
        }
        virtual ~LeftCommand()override{}
    };

    class RightCommand : public Command{
    public:
        void Execute(Unit::Hero* iter) override{
            iter -> Step_Right();
        }
        virtual ~RightCommand()override{}
    };

    class UpCommand : public Command{
    public:
        void Execute(Unit::Hero* iter) override{
            iter -> Step_Up();
        }
        virtual ~UpCommand()override{}
    };

    class DownCommand : public Command{
    public:
        void Execute(Unit::Hero* iter) override{
            iter -> Step_Down();
        }
        virtual ~DownCommand()override{}
    };

}
#endif // COMMAND_H
