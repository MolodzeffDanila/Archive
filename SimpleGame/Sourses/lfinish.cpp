#include "Headers/lfinish.h"

void Types_of_cell::Lfinish::SetGraph(QGraphicsScene *scene){
    scene_m = scene;
    cell2_pixmap=scene->addPixmap(QPixmap(":/pref/resourses/ground.jpg"));
    cell2_pixmap -> setOffset(x*110, y*110);
    cell_pixmap = scene->addPixmap(QPixmap(":/pref/resourses/finish.png"));
    cell_pixmap -> setOffset(x*110, y*110);
    cell_pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
}
