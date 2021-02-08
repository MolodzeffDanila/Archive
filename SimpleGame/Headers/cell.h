#ifndef FIELD_CELL_H
#define FIELD_CELL_H

#include "Headers/types_of_cells.h"
#include "Headers/observer.h"
#include "Headers/subject.h"

namespace Field {

    class Cell : public Logging::Subject {
        int x;
        int y;
        bool is_passable;
        unsigned int type_of_cell;
        std::list<Logging::Bridge*> list_of_observers_;
    public:
        Types_of_cell::Types_of_cells* obj;
        Cell();
        ~Cell();
        bool Is_passable();
        void Add_cell(Types_of_cell::Types_of_cells* cell);
        void Remove_obj(){
            if(obj){
                is_passable=true;
                delete obj;
            }
        }
        bool Check_Enem();
        void Subscribe(Logging::Bridge* abstr)override;
        void Unsubscribe(Logging::Bridge* abstr)override;
        void Notify()override;
        friend std::ostream& operator<<(std::ostream &out, Cell* cell){
            out << "Current cell id is: " << cell->obj->get_type_of_cell() << "\n";
            return out;
        }
    };

    class CellObserver : public Logging::Observer{
       std::fstream file;
       bool is_file,is_cons;
    public:
        CellObserver(bool is_f,bool is_c){
            is_file=is_f;
            is_cons=is_c;
            if(is_file){
               file.open("Cell_logs.txt", std::fstream::in | std::fstream::out | std::fstream::app);
                }
            }
        virtual ~CellObserver(){
            if(is_file){
                 file.close();
            }
        }
        void update(Logging::Subject* cell)override{
            if(is_file){
                 file << dynamic_cast<Cell*>(cell);
            }
           if(is_cons){
                std::cout<<dynamic_cast<Cell*>(cell);
           }
        }
    };
}

#endif //FIELD_CELL_H
