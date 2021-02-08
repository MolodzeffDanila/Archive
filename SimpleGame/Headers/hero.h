#ifndef HERO_H
#define HERO_H

#include "Headers/using_libs.h"
#include "Headers/types_of_cells.h"
#include "Headers/cell.h"
#include "Headers/field.h"
#include "Headers/observer.h"
#include "Headers/subject.h"

enum State{STAY, GO, PATROUL};
enum Fight{ATTACK, DEFEND};

namespace Unit {
template<typename T1, typename T2>
class Enemy;
class AbsStrategy;

    class Hero : public Logging::Subject{
        Field::Field* map;
        bool is_dead=false;
        int coord_x;
        int coord_y;
        int defence,defence_baff;
        int attack,attack_baff;
        int coins;
        int health;
        Field::Cell* cur_cell;
        AbsStrategy* abstractStrategy;
        QGraphicsScene* playerScene;
        QGraphicsPixmapItem* Unit;
        std::list<Logging::Bridge*> list_of_observers_;
    public:
        Hero(int x, int y, QGraphicsScene* scene, Field::Cell& cell);
        void Move();
        void Set_bonus_def(int def);
        void Set_bonus_att(int att);
        void Set_def(int def);
        void Set_att(int att);
        void Set_coins(int coins);
        void Set_curr_cell(Field::Cell& cell_obj);
        void Set_strategy(AbsStrategy* strategy);
        void SetHP(int hp);
        void Set_map(Field::Field* map);
        bool Is_won();
        bool Is_End_Loc();
        void Reset_Graph();
        Field::Cell& Get_curr();
        void Set_coord(int x, int y);
        int Get_coord_x();
        int Get_coord_y();
        int Get_bonus_def();
        int Get_bonus_att();
        QString Get_Info();
        void  Hit(int val);
        int Get_Attack();
        int Get_Defence();
        int Get_HP();
        int Get_Coins();

        void Step_Left();
        void Step_Right();
        void Step_Up();
        void Step_Down();
        void Stay();

        void Subscribe(Logging::Bridge* abstr)override;
        void Unsubscribe(Logging::Bridge* abstr)override;
        void Notify()override;

        void operator+=(Unit::Enemy<State,Fight>* const& enemy);

        void operator+(Types_of_cell::Types_of_cells* const& cell);

        friend std::ostream& operator<<(std::ostream& out,Hero* hero){
            out <<"Hero moved to:\n x="<<hero->Get_coord_x()<<"\n y="<<hero->Get_coord_y()<<"\n";
            out <<"\nCurrent bonuses:\n defencebonus="<<hero->Get_bonus_def()<<"\n attackbonus="<<hero->Get_bonus_att()<<"\n";
            return out;
        }

        ~Hero();
    };

    template<typename T1, typename T2>
    class Enemy{
        Unit::Hero* aim_=nullptr;
        Field::Field* map;
        int curr_x;
        int curr_y;
        int defense;
        int attack;
        int fire_attack;
        int hp;
        QGraphicsScene* enemyScene;
        bool is_dead=false;
        int direction;
        int metric_x,metric_y;
    public:
        T1 move_condition=STAY;
        T2 fight_condition=ATTACK;
        QGraphicsPixmapItem* enemyUnit;
        Enemy(int x, int y, QGraphicsScene* scene){
            direction = 1;
            attack = 3;
            curr_x = x;
            curr_y = y;
            enemyScene = scene;
            enemyUnit = enemyScene -> addPixmap(QPixmap(":/pref/resourses/enemy.png"));
            defense = 2;
            hp = 12;
            Move();
        }

        void ChangeCondition(T1 new_cond){
            this->move_condition=new_cond;
        }

        void ChangeFightCondition(T2 new_cond){
            this->fight_condition=new_cond;
        }

        Hero* Get_Aim(){
            return this->aim_;
        }

        void Set_Aim(Unit::Hero* aim){
            this->aim_=aim;
            ChangeCondition(GO);
        }

        void Moving(){
            if(!is_dead && move_condition==PATROUL){
                if(direction==1){
                    if(map->Get_Cell(curr_x,curr_y-1).Is_passable()){
                        SetCurY(curr_y-1);
                        Move();
                    }else if(map->Get_Cell(curr_x-1,curr_y).Is_passable()){
                        direction=4;
                    }else if(map->Get_Cell(curr_x+1,curr_y).Is_passable() && GetCurY()+1<map->width){
                        direction=2;
                    }else{
                        direction=3;
                    }
                }
                if(direction==2){
                    if(map->Get_Cell(curr_x+1,curr_y).Is_passable() && GetCurY()+1<map->width ){
                        SetCurX(curr_x+1);
                        Move();
                    }else if(map->Get_Cell(curr_x,curr_y-1).Is_passable()){
                        direction=1;
                    }else if(map->Get_Cell(curr_x,curr_y+1).Is_passable()){
                        direction=3;
                    }else{
                        direction=4;
                    }
                }
                if(direction==3){
                    if(map->Get_Cell(curr_x,curr_y+1).Is_passable()){
                        SetCurY(curr_y+1);
                        Move();
                    }else if(map->Get_Cell(curr_x+1,curr_y).Is_passable() && GetCurY()+1<map->width-1){
                        direction=2;
                    }else if(map->Get_Cell(curr_x-1,curr_y).Is_passable()){
                        direction=4;
                    }else{
                        direction=1;
                    }
                }
                if(direction==4){
                    if(map->Get_Cell(curr_x-1,curr_y).Is_passable() && GetCurX()-1>=0){
                        SetCurX(curr_x-1);
                        Move();
                    }else if(map->Get_Cell(curr_x,curr_y+1).Is_passable()){
                        direction=3;
                    }else if(map->Get_Cell(curr_x,curr_y-1).Is_passable()){
                        direction=1;
                    }else{
                        direction=2;
                    }
                }
            }
            if(!is_dead && move_condition==GO){
                metric_x=aim_->Get_coord_x()-curr_x;
                metric_y=aim_->Get_coord_y()-curr_y;
                if(metric_x<=2 && metric_x>=-2 && metric_y>=-2 && metric_y<=2){
                    SetCurX(aim_->Get_coord_x());
                    SetCurY(aim_->Get_coord_y());
                }
        }
        }
        void SetMap(Field::Field* level){
            this->map = level;
        }
        void Move(){
            enemyUnit -> setOffset(curr_x*110+10, curr_y*110+10);
        }
        void SetCurX(int x){
            curr_x = x;
        }
        void SetCurY(int y){
            curr_y = y;
        }
        int GetCurX(){
            return curr_x;
        }
        int GetCurY(){
            return curr_y;
        }
        int GetHealth(){
            return hp;
        }
        bool IsDead(){
            return (is_dead == true);
        }
        void operator+=(Unit::Hero* const& hero){
            if(this->is_dead){
                return;
            }
            if((curr_x == hero->Get_coord_x()) && (curr_y == hero->Get_coord_y())){
                hero->Hit(attack);
            }
        }

        void Hit(int val){
            if(fight_condition==DEFEND){
                defense++;
                attack--;
            }
            if(fight_condition==ATTACK){
                attack++;
                defense--;
            }
            hp-=val+defense;
            if(hp < 0){
                hp = 0;
                enemyScene->removeItem(enemyUnit );
                enemyUnit  = enemyScene -> addPixmap(QPixmap(":/pref/resourses/grave.png"));
                enemyUnit  -> setOffset(curr_x*110, curr_y*110);
                this->is_dead=true;
            }
        }

        bool IsKilled(){
             return (hp == 0);
        }
        ~Enemy(){
            //delete enemyUnit;
        }
    };

    class AbsStrategy{
    public:
        virtual void Interact(Hero* unit) = 0;
    };

    class DefaultStrategy : public AbsStrategy {
    public:
        void Interact(Hero* unit) override {
            unit->Set_bonus_def(0);
            unit->Set_bonus_att(0);
        }
    };

    class FortressStrategy : public AbsStrategy {
    public:
        void Interact(Hero* unit) override {
            unit->Set_bonus_def(5);
            unit->Set_bonus_att(-1);
            unit->Set_coins(2);
        }
    };

    class DungeonStrategy : public AbsStrategy {
    public:
        void Interact(Hero* unit) override {
            unit->Set_bonus_def(0);
            unit->Set_bonus_att(0);
            unit->Set_coins(0);
        }
    };
}

namespace Logging {

    class HeroObserver : public Observer{
        std::fstream file;
        bool is_file,is_cons;
    public:
        HeroObserver(bool is_f,bool is_c){
            is_file=is_f;
            is_cons=is_c;
            if(is_file){
               file.open("Hero_logs.txt", std::fstream::in | std::fstream::out | std::fstream::app);
                }
            }
        ~HeroObserver(){
           if(is_file){
                file.close();
           }
        }
        void update(Logging::Subject* sub)override{
            if(is_file){
                 file << dynamic_cast<Unit::Hero*>(sub);
            }
           if(is_cons){
                std::cout<<dynamic_cast<Unit::Hero*>(sub);
           }
        }
    };
}

#endif // HERO_H
