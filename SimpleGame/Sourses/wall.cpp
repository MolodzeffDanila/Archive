#include "Headers/wall.h"

void Types_of_cell::Wall::SetGraph(QGraphicsScene *scene){
    if(scene_m==nullptr){
        scene_m = scene;
    }
    cell_pixmap = scene_m->addPixmap(QPixmap(":/pref/resourses/wall.png"));
    cell_pixmap -> setOffset(x*110, y*110);
    cell_pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
}

