#ifndef FLATLAND_H
#define FLATLAND_H
#include "Headers/types_of_cells.h"
namespace Types_of_cell{
    class Flatland : public Types_of_cells{
        int x;
        int y;
        bool is_used;
        QGraphicsScene* scene_m;
        QGraphicsPixmapItem* cell_pixmap;
        int id = 2;
    public:
        Flatland(int x,int y) : x(x),y(y), is_used(false)  {}
        ~Flatland(){}
        void SetGraph(QGraphicsScene* scene)override;
        int get_type_of_cell() override{
            return this->id;
        }
        void Set_used() override{
                is_used = true;
            }
        bool Is_used() override {
                return is_used == true;
        }
        void Remove_Graph()override{
            scene_m->removeItem(cell_pixmap);
        }
        QGraphicsPixmapItem* Get_pic1()override{
            return this->cell_pixmap;
        }
        QGraphicsPixmapItem* Get_pic2()override{
            return nullptr;
        }
    };
}
#endif // FLATLAND_H
