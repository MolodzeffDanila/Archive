#ifndef FIELD_FIELD_H
#define FIELD_FIELD_H

#include "Headers/cell.h"
#include "Headers/using_libs.h"

namespace Field {

    class Field {
        protected:
            Cell** map_array;
            Field* field_;
        public:
            unsigned int width;
            unsigned int height;

            Field(Field const& elem);
            Field& operator=(Field const& elem);
            Field operator=(Field const elem);
            Field(Field&& elem);
            Field& operator=(Field&& elem);

            void Repaint(int** level);

            ~Field();

            Field(int width,int height, int** level, QGraphicsScene *scene,CellObserver* cell_obser);
            Field *GetField();
            Cell&  Get_Cell(int x,int y);
        private:
            int level_1;
            QGraphicsScene *scene_;

    };

}
#endif //FIELD_FIELD_H
