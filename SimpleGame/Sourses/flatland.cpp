#include "Headers/flatland.h"
#include "Headers/using_libs.h"

void Types_of_cell::Flatland::SetGraph(QGraphicsScene *scene){
    scene_m = scene;
    cell_pixmap = scene->addPixmap(QPixmap(":/pref/resourses/cell2.jpg"));
    cell_pixmap -> setOffset(x*110, y*110);
    cell_pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
}

