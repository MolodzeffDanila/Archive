#ifndef FINISH_H
#define FINISH_H
#include "Headers/using_libs.h"
#include "Headers/types_of_cells.h"
namespace Types_of_cell{
    class Finish : public Types_of_cells{
        int x;
        int y;
        bool is_used;
        QGraphicsScene* scene_m;
        QGraphicsPixmapItem* cell_pixmap;
        QGraphicsPixmapItem* cell2_pixmap;
        int id = 1;
    public:
        Finish(int x,int y) : x(x),y(y), is_used(false)  {}
        ~Finish(){}
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
            scene_m->removeItem(cell2_pixmap);
        }
        QGraphicsPixmapItem* Get_pic1()override{
            return this->cell_pixmap;
        }
        QGraphicsPixmapItem* Get_pic2()override{
            return this->cell2_pixmap;
        }
    };
}
#endif // FINISH_H
