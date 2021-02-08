#ifndef FACADE_H
#define FACADE_H
#include "Headers/using_libs.h"
#include "Headers/field.h"
#include "Headers/observer.h"
#include "Headers/hero.h"
#include "Headers/subject.h"
#include "Headers/command.h"
#include "Headers/mementomori.h"
#include "Headers/fileexeption.h"

namespace Field {
    class ConcreteMoment;
    class ConcreteCareTaker;
    class Condition;
    class Facade{
        private:
            QGraphicsScene *facade_scene;
            std::string filename="";
            Field* created_map;
            Field* loc_map;
            Unit::Hero* hero;
            CellObserver* cell_observer;
            Logging::HeroObserver* hero_observer;
            Logging::Bridge* bridge;
            Command::Command* command;
            int hero_coord_x_;
            int hero_coord_y_;
            std::vector<Unit::Enemy<State, Fight>*> enemies;
            Unit::Enemy<State,Fight>* enemy1_=nullptr;
            Unit::Enemy<State,Fight>* enemy2_=nullptr;
            Unit::Enemy<State,Fight>* enemy3_=nullptr;
            Unit::Enemy<State,Fight>* enemy4_=nullptr;
            Condition* condition = nullptr;
            QTimer* delay_;
            int loc_x,loc_y;
            bool is_dungeon=false;
        public:
            Facade(QGraphicsScene *scene, int val, CellObserver* cell_obser);
            void SetCommand(Command::Command* command);
            void Set_Hero_coord(int x,int y);
            void Set_hero_observer(Logging::HeroObserver* hero_observer);
            void Set_cell_observer(CellObserver* cell_observer);
            void Set_bridge(Logging::Bridge* bridge);
            void Start_location(QGraphicsScene *scene);
            void Is_Fight();
            void Request();
            void SetPath(std::string& path);
            std::string GetPath();

            ConcreteMoment* Save();
            void Load();
            void Restore(ConcreteMoment* mem);
            ConcreteCareTaker* care_taker;
            void Moving();
            void SpawnEnemies();
            void RemoveEnemies();
            void ChangeCondition(Condition* cond);
            bool Is_End_Loc();
            void End_Loc();
            bool Is_Dungeon();
            void Remember_coord(int x,int y);
            Unit::Hero* GetHero();
            bool IsWon();
            Field* GetMap();
            void Execute();
            ~Facade();
    };

    class Condition{
    protected:
        Facade* facade;
    public:
        void setFacade(Facade* item){
            facade = item;
        }
        virtual void Handle() = 0;
        virtual ~Condition(){}
    };

    class HeroCond : public Condition{
    public:
        void Handle()override;
    };

    class EnemyCond : public Condition{
    public:
        void Handle()override{
            this->facade->Moving();
            this->facade->Is_Fight();
            this->facade->ChangeCondition(new HeroCond);
        }
    };

    class ConcreteMoment : public Moment{
    public:
        std::string date()override;
        int coordX;
        int coordY;
        int hero_health;
        int hero_coins;
        int attack;
        int defence;
        std::string date_;
        std::fstream file_;
        friend CareTaker;
        ConcreteMoment(Facade* facade);
        void WriteFile()override;
        void ReadFile()override;
        void SetDate(std::string path);
    };

    class ConcreteCareTaker : public CareTaker{
           std::vector<ConcreteMoment*> mementos;
           Facade* facade_ = nullptr;
    public:
           void BackUp()override;
           void Undo()override;
           void SetFacade(Facade* facade);
           Facade* GetMemento();
           void SetMemento(ConcreteMoment* mem);
    };

}

#endif // FACADE_H
