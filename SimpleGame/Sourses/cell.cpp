#include "Headers/cell.h"

Field::Cell::Cell(){
    Cell::is_passable=true;
    obj=nullptr;
}

void Field::Cell::Add_cell(Types_of_cell::Types_of_cells* cell){
    obj=cell;
    int id = cell->get_type_of_cell();
    if ( id == 3 || id==12){
        is_passable = false;
    }

}

bool Field::Cell::Check_Enem(){
    int flag=0;
    for (int i=0;i<4;i++) {
        if(obj->enemy[i]==true){
            flag++;
        }
    }
    if(flag>0){
        return true;
    }else{
        return false;
    }
}

bool Field::Cell::Is_passable(){
    return this->is_passable;
}


void Field::Cell::Subscribe(Logging::Bridge* abstr){
    this->list_of_observers_.push_back(abstr);
}

void Field::Cell::Unsubscribe(Logging::Bridge* abstr){
    this->list_of_observers_.remove(abstr);
}

void Field::Cell::Notify(){
    std::list<Logging::Bridge*>::iterator iterator = list_of_observers_.begin();
            while (iterator != list_of_observers_.end()) {
              (*iterator)->Operation(this);
              ++iterator;
        }
}

Field::Cell::~Cell(){}
