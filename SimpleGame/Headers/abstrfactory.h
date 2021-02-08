#ifndef ABSTRFACTORY_H
#define ABSTRFACTORY_H
#include "Headers/start.h"
#include "Headers/finish.h"
#include "Headers/flatland.h"
#include "Headers/mountain.h"
#include "Headers/dungeon.h"
#include "Headers/fortress.h"
#include "Headers/lstart.h"
#include "Headers/lfinish.h"
#include "Headers/wall.h"
#include "Headers/ground.h"

namespace  Factory{

    class AbstrFactory
    {
    public:
        virtual Types_of_cell::Types_of_cells* Create_Flatland(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Start(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Finish(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Mountain(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Dungeon(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Fortress(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Lstart(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Lfinish(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Wall(int x, int y) const = 0;
        virtual Types_of_cell::Types_of_cells* Create_Ground(int x, int y) const = 0;
    };

    class RealFactory : public AbstrFactory{
      public:
        Types_of_cell::Types_of_cells* Create_Flatland(int x, int y) const override{
                return new Types_of_cell::Flatland(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Start(int x, int y) const override{
                return new Types_of_cell::Start(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Finish(int x, int y) const override{
                return new Types_of_cell::Finish(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Mountain(int x, int y) const override{
                return new Types_of_cell::Mountain(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Dungeon(int x, int y) const override{
                return new Types_of_cell::Dungeon(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Fortress(int x, int y) const override{
                return new Types_of_cell::Fortress(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Lstart(int x, int y) const override{
                return new Types_of_cell::Lstart(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Lfinish(int x, int y) const override{
                return new Types_of_cell::Lfinish(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Wall(int x, int y) const override{
                return new Types_of_cell::Wall(x, y);
        }
        Types_of_cell::Types_of_cells* Create_Ground(int x, int y) const override{
                return new Types_of_cell::Ground(x, y);
        }
    };
}

#endif // ABSTRFACTORY_H
