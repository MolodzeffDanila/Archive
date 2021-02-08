#include "Headers/ground.h"

void Types_of_cell::Ground::SetGraph(QGraphicsScene *scene){
    scene_m = scene;
    cell_pixmap = scene->addPixmap(QPixmap(":/pref/resourses/ground.png"));
    cell_pixmap -> setOffset(x*110, y*110);
    cell_pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
}
