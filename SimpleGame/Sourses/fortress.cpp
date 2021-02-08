#include "Headers/fortress.h"

void Types_of_cell::Fortress::SetGraph(QGraphicsScene* scene){
    scene_m = scene;
    cell2_pixmap=scene->addPixmap(QPixmap(":/pref/resourses/cell2.jpg"));
    cell2_pixmap -> setOffset(x*110, y*110);
    cell2_pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
    cell_pixmap=scene->addPixmap(QPixmap(":/pref/resourses/fortress.png"));
    cell_pixmap -> setOffset(x*110, y*110);

}
