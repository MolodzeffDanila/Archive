#ifndef TYPES_OF_CELLS_H
#define TYPES_OF_CELLS_H

#include "Headers/using_libs.h"

namespace Types_of_cell{
    class Types_of_cells{
    public:
        bool enemy[4]={true,true,true,true};
        void virtual SetGraph(QGraphicsScene* scene)=0;
        int virtual get_type_of_cell() =0;
        void virtual Set_used() = 0;
        bool virtual Is_used() = 0;
        virtual QGraphicsPixmapItem*  Get_pic1()=0;
        virtual QGraphicsPixmapItem* Get_pic2()=0;
        virtual void Remove_Graph()=0;
        virtual ~Types_of_cells(){}
    };
}
#endif // TYPES_OF_CELLS_H
