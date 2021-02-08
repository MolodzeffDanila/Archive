#include "Headers/mountain.h"
#include "Headers/using_libs.h"

void Types_of_cell::Mountain::SetGraph(QGraphicsScene *scene){
    scene_m = scene;
    cell_pixmap=scene->addPixmap(QPixmap(":/pref/resourses/mountain.png"));
    cell_pixmap -> setOffset(x*110, y*110);
    cell_pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
}
