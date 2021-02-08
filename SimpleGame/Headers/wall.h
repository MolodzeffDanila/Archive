#ifndef WALL_H
#define WALL_H
#include "Headers/types_of_cells.h"
#include "Headers/using_libs.h"
namespace Types_of_cell{
    class Wall : public Types_of_cells{
        int x;
        int y;
        bool is_used;
        QGraphicsScene* scene_m;
        QGraphicsPixmapItem* cell_pixmap;
        int id = 12;
    public:
        Wall(int x,int y) : x(x), y(y),is_used(false){scene_m=nullptr;}
        void SetGraph(QGraphicsScene* scene) override;
        ~Wall(){

        }
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
#endif // WALL_H
