#include "Headers/hero.h"
#include "Headers/using_libs.h"
#include <iostream>

Unit::Hero::Hero(int x, int y, QGraphicsScene* scene, Field::Cell& cell){
    this->Set_curr_cell(cell);
    coord_x=x;
    coord_y=y;
    playerScene=scene;
    Unit = scene -> addPixmap(QPixmap(":/pref/resourses/Slavick.png"));
    defence=2;
    defence_baff=0;
    attack=5;
    attack_baff=0;
    health=100;
    coins=0;
    this->Move();
}

int Unit::Hero::Get_Attack(){
    return this->attack;
}

void Unit::Hero::Reset_Graph(){
    playerScene->removeItem(Unit);
    Unit = playerScene -> addPixmap(QPixmap(":/pref/resourses/Slavick.png"));
}

bool Unit::Hero::Is_won(){
    if(this->cur_cell->obj){
        return ((this->cur_cell->obj->get_type_of_cell())==1);
    }else{
        return false;
    }
}

bool Unit::Hero::Is_End_Loc(){
    if(this->cur_cell->obj){
        return ((this->cur_cell->obj->get_type_of_cell())==15);
    }else{
        return false;
    }
}

void Unit::Hero::Set_coord(int x, int y){
    this->coord_x=x;
    this->coord_y=y;
}

void Unit::Hero::Set_map(Field::Field *map){
    this->map=map;
}

void Unit::Hero::Set_strategy(AbsStrategy* strategy){
    abstractStrategy=strategy;
}

void Unit::Hero::Set_curr_cell(Field::Cell &cell_obj){
    this -> cur_cell = &cell_obj;
    *this + cur_cell -> obj;
}

int Unit::Hero::Get_HP(){
    return this->health;
}

int Unit::Hero::Get_Defence(){
    return this->defence;
}

int Unit::Hero::Get_Coins(){
    return this->coins;
}

void Unit::Hero::operator+=(Unit::Enemy<State,Fight>* const& enemy){
    if(this->is_dead){
        return;
    }
    if((coord_x == enemy->GetCurX()) && (coord_y == enemy->GetCurY())){
        enemy->Hit(attack);
    }
}

void Unit::Hero::operator+(Types_of_cell::Types_of_cells *const &cell){
    if ((cell->get_type_of_cell() < 4)){
        DefaultStrategy* defaultStrategy = new DefaultStrategy();
        this->Set_strategy(defaultStrategy);
    }
    if ((cell->get_type_of_cell() == 4) && cell->Is_used()==false){
        DungeonStrategy* dungeonStrategy = new DungeonStrategy();
        this->Set_strategy(dungeonStrategy);
        cell->Set_used();
    }
    if ((cell->get_type_of_cell() == 5) && cell->Is_used()==false){
        FortressStrategy* fortressStrategy = new FortressStrategy();
        this->Set_strategy(fortressStrategy);
        cell->Set_used();
    }
    abstractStrategy->Interact(this);
}

void Unit::Hero::Move(){
    Unit -> setOffset(20+coord_x*110, 20+coord_y*110);
    this->Notify();
}

Field::Cell& Unit::Hero::Get_curr(){
    return this->map->Get_Cell(coord_x,coord_y);
}

void Unit::Hero::Step_Up(){
    if(coord_y<1 || health<=0){
        return;
    }
    Field::Cell& next_cell=this->map->Get_Cell(coord_x,coord_y-1);
    if(next_cell.Is_passable()){
        this->Set_coord(coord_x,coord_y-1);
        this->Set_curr_cell(this->Get_curr());
        this->Move();
    }

}

void Unit::Hero::Stay(){
    this->Set_coord(coord_x,coord_y);
    this->Set_curr_cell(this->Get_curr());
    this->Move();
}

void  Unit::Hero::Step_Down(){
    if(((coord_y+1)==this->map->height) || health<=0){
        return;
    }
    Field::Cell& next_cell=this->map->Get_Cell(coord_x,coord_y+1);
    if(next_cell.Is_passable()){
        this->Set_coord(coord_x,coord_y+1);
        this->Set_curr_cell(this->Get_curr());
        this->Move();
    }
}

void Unit::Hero::Step_Left(){
    if(coord_x<1 || health<=0){
        return;
    }
    Field::Cell& next_cell=this->map->Get_Cell(coord_x-1,coord_y);
    if(next_cell.Is_passable()){
        this->Set_coord(coord_x-1,coord_y);
        this->Set_curr_cell(this->Get_curr());
        this->Move();
    }
}

void Unit::Hero::Step_Right(){
    if(((coord_x+1)==this->map->width) || health<=0 ){
        return;
    }
    Field::Cell& next_cell=this->map->Get_Cell(coord_x+1,coord_y);
    if(next_cell.Is_passable()){
        this->Set_coord(coord_x+1,coord_y);
        this->Set_curr_cell(this->Get_curr());
        this->Move();
    }
}

QString Unit::Hero::Get_Info(){
    QString res="Attack: "+QString::number(attack)+" Attack_bonus: "+QString::number(attack_baff)+"\n";
    res=res+"Defence:"+QString::number(defence)+" Defence_bonus: "+QString::number(defence_baff)+"\n";
    res=res+"Coins:"+QString::number(coins)+"\n";
    res=res+"Health:"+QString::number(health)+"\n";
    return res;
}

void Unit::Hero::Set_bonus_def(int val){
    defence_baff = val;
}
void Unit::Hero::Set_bonus_att(int val){
    attack_baff = val;
}
void Unit::Hero::Set_coins(int val){
    coins += val;
}

void Unit::Hero::SetHP(int hp){
    this->health=hp;
}

void Unit::Hero::Set_def(int def){
    this->defence=def;
}

void Unit::Hero::Set_att(int att){
    this->attack=att;
}

int Unit::Hero::Get_coord_x(){
    return this->coord_x;
}

int Unit::Hero::Get_coord_y(){
    return this->coord_y;
}

int Unit::Hero::Get_bonus_def(){
    return this->defence_baff;
}
int Unit::Hero::Get_bonus_att(){
    return this->attack_baff;
}

void Unit::Hero::Hit(int val){
    if(defence<val){
        this->health-=val+defence;
    }
    if(health <= 0){
        health = 0;
        playerScene->removeItem(Unit);
        Unit = playerScene -> addPixmap(QPixmap(":/pref/resourses/grave.png"));
        Unit -> setOffset(coord_x*110, coord_y*110);
    }
}

void Unit::Hero::Subscribe(Logging::Bridge* abstr){
    this->list_of_observers_.push_back(abstr);
}

void Unit::Hero::Unsubscribe(Logging::Bridge* abstr){
    this->list_of_observers_.remove(abstr);
}

void Unit::Hero::Notify(){
    std::list<Logging::Bridge*>::iterator iterator = list_of_observers_.begin();
            while (iterator != list_of_observers_.end()) {
              (*iterator)->Operation(this);
              ++iterator;
        }
}


Unit::Hero::~Hero(){}
