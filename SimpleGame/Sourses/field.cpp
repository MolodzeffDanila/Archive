#include "Headers/field.h"
#include "Headers/abstrfactory.h"

Field::Field::Field(int width,int height, int** level, QGraphicsScene *scene,CellObserver* cell_observer) {
    this->map_array=new Cell*[height];
    scene_=scene;
    Logging::Bridge* bridge=new Logging::Bridge(cell_observer);
    for (int i = 0; i < height; i++){
            map_array[i] = new Cell[width];
    }    
    for (int i=0;i<height;i++) {
        for(int j=0;j<width;j++){
            map_array[i][j] = Cell();
            int flag = level[i][j];
            Factory::RealFactory factory;
            switch (flag) {
                case 0:
                    map_array[i][j].Add_cell(factory.Create_Start(j,i));
                    break;
                case 1:
                    map_array[i][j].Add_cell(factory.Create_Finish(j,i));
                    break;
                case 2:
                    map_array[i][j].Add_cell(factory.Create_Flatland(j,i));
                    break;
                case 3:
                    map_array[i][j].Add_cell(factory.Create_Mountain(j,i));
                    break;
                case 4:
                    map_array[i][j].Add_cell(factory.Create_Dungeon(j,i));
                    break;
                case 5:
                    map_array[i][j].Add_cell(factory.Create_Fortress(j,i));
                    break;
            }
            map_array[i][j].obj->SetGraph(scene);
            map_array[i][j].Subscribe(bridge);
            map_array[i][j].Notify();
            map_array[i][j].Unsubscribe(bridge);
        }
    }
    this->height=height;
    this->width=width;
    delete cell_observer;
}

Field::Field::~Field(){
    for (unsigned int i = 0; i < height; i++){
        delete [] map_array[i];
    }
    delete [] map_array;
}

void Field::Field::Repaint(int **level){
    for (unsigned int i = 0; i < height; i++){
        for (int j=0;j<width;j++) {
                map_array[i][j].obj->Remove_Graph();
                map_array[i][j].Remove_obj();
        }
    }
    Cell** tmp= new Cell*[height];
    for (int i=0;i<height;i++) {
        tmp[i] = new Cell[width];
        for(int j=0;j<width;j++){
            int flag = level[i][j];
            Factory::RealFactory factory;
              switch (flag) {
                case 0:
                    tmp[i][j].Add_cell(factory.Create_Start(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 1:
                    tmp[i][j].Add_cell(factory.Create_Finish(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 2:
                    tmp[i][j].Add_cell(factory.Create_Flatland(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 3:
                    tmp[i][j].Add_cell(factory.Create_Mountain(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 4:
                    tmp[i][j].Add_cell(factory.Create_Dungeon(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 5:
                    tmp[i][j].Add_cell(factory.Create_Fortress(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 10:
                    tmp[i][j].Add_cell(factory.Create_Lstart(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 12:
                    tmp[i][j].Add_cell(factory.Create_Wall(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 13:
                    tmp[i][j].Add_cell(factory.Create_Ground(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
                case 15:
                    tmp[i][j].Add_cell(factory.Create_Lfinish(j,i));
                    tmp[i][j].obj->SetGraph(scene_);
                    break;
            }

        }

    }
    map_array=tmp;
}

Field::Field::Field(Field const& elem){
    field_=elem.field_;
    this->width=elem.width;
    this->height=elem.height;
    this->map_array = new Cell*[height];
    for (int i = 0;i<height;i++) {
        this->map_array[i] = new Cell[width];
    }
    for (int i = 0;i<height;i++) {
        for (int j = 0;j<width;j++) {
            this->map_array[i][j]=elem.map_array[i][j];
        }
    }

}

Field::Field& Field::Field::operator=(Field const& elem){
    if(this != &elem){
        field_=elem.field_;
        for (int i=0;i<width;i++) {
            delete [] map_array[i];
        }
        delete [] map_array;

        this->height=elem.height;
        this->width=elem.width;
        this->map_array=new Cell*[height];
        for (int i=0;i<height;i++) {
            map_array[i] = new Cell[width];
        }
    }
}

Field::Field& Field::Field::operator=(Field&& elem){
    if(this != &elem){
        for (int i=0;i<width;i++) {
            delete [] map_array[i];
        }
        delete [] map_array;

        this->map_array=elem.map_array;
        this->field_=elem.field_;

        elem.map_array=nullptr;
        elem.field_=nullptr;
    }
    return *this;
}

Field::Field::Field(Field&& elem){
    this -> map_array = elem.map_array;
    this->field_ = elem.field_;
    elem.map_array = nullptr;
    elem.field_ = nullptr;
}

Field::Field *Field::Field::GetField(){
    return field_;
}

Field::Cell& Field::Field::Get_Cell(int x,int y){
    return map_array[y][x];
}


