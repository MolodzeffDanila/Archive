#include "Headers/facade.h"

Field::Facade::Facade(QGraphicsScene *scene, int val,CellObserver* cell_obser){
    int** creating_level;
    int level_2[10][10] = { {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 2, 4, 2, 2, 2, 4, 2, 2, 2},
                            {2, 2, 2, 2, 4, 2, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 2, 5, 2, 2, 2, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2, 3, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 3, 5},
                            {2, 2, 2, 2, 2, 2, 2, 2, 5, 1}};
    int fheight=10;
    int fwidth=10;

    int start_x=0;
    int start_y=0;

    creating_level= new int*[fheight];

    for(int i=0;i<fheight;i++){
        creating_level[i]= new int[fwidth];
    }

    for(int i = 0;i<fheight;i++){
        for(int j = 0;j<fheight;j++){
            creating_level[i][j]=level_2[i][j];
            if(creating_level[i][j]==0){
                start_x=j;
                start_y=i;
            }
        }
    }

    this->hero_coord_x_=start_x;
    this->hero_coord_y_=start_y;
    this->facade_scene=scene;
    created_map = new Field(fwidth,fheight,creating_level, scene,cell_obser);
    hero = new Unit::Hero(start_x,start_y,scene,created_map->Get_Cell(start_x,start_y));
    hero->Set_map(created_map);
    ChangeCondition(new HeroCond());
}

void Field::Facade::Moving(){
    if(!is_dungeon){
        return;
    }
    if(enemy1_!=nullptr){
        enemy1_->Moving();
    }
    if(enemy2_!=nullptr){
        enemy2_->Moving();
    }
    if(enemy3_!=nullptr){
        enemy3_->Moving();
    }
    if(enemy4_!=nullptr){
        enemy4_->Moving();
    }
    Is_Fight();
}

void Field::Facade::Remember_coord(int x, int y){
    this->hero_coord_x_=x;
    this->hero_coord_y_=y;
}

void Field::Facade::Start_location(QGraphicsScene *scene){
    int** creating_loc;
    int location[10][10] = {{12, 12, 12, 12, 12, 12, 12, 12, 12, 12},
                            {10, 13, 13, 13, 13, 13, 13, 13, 13, 12},
                            {12, 13, 12, 13, 12, 13, 12, 13, 13, 12},
                            {12, 13, 12, 13, 12, 13, 12, 12, 13, 12},
                            {12, 13, 12, 12, 12, 13, 12, 12, 13, 12},
                            {12, 13, 13, 13, 12, 13, 13, 13, 13, 12},
                            {12, 13, 12, 13, 13, 13, 12, 13, 13, 12},
                            {12, 13, 12, 13, 13, 13, 12, 12, 13, 12},
                            {12, 13, 12, 12, 13, 13, 13, 13, 13, 15},
                            {12, 12, 12, 12, 12, 12, 12, 12, 12, 12}};

    int fheight=10;
    int fwidth=10;

    int start_x=0;
    int start_y=0;

    creating_loc= new int*[fheight];

    for(int i=0;i<fheight;i++){
        creating_loc[i]= new int[fwidth];
    }

    for(int i = 0;i<fheight;i++){
        for(int j = 0;j<fwidth;j++){
            creating_loc[i][j]=location[i][j];
            if(creating_loc[i][j]==10){
                start_x=j;
                start_y=i;
            }
        }
    }

    Remember_coord(hero->Get_coord_x(),hero->Get_coord_y());
    loc_x=hero_coord_x_;
    loc_y=hero_coord_y_;

    created_map->Repaint(creating_loc);
    hero->Set_coord(start_x,start_y);
    hero->Reset_Graph();
    hero->Move();
    SpawnEnemies();
    is_dungeon=true;
}

void Field::Facade::SetPath(std::string& path){
    this->filename=path;
}

std::string Field::Facade::GetPath(){
    return filename;
}

bool Field::Facade::Is_Dungeon(){
    return is_dungeon;
}

void Field::Facade::SpawnEnemies(){
            enemy1_ = new Unit::Enemy<State,Fight>(8,8,this->facade_scene);
            enemy1_->ChangeCondition(PATROUL);
            enemy1_->SetMap(created_map);

            enemy2_ = new Unit::Enemy<State,Fight>(5,8,this->facade_scene);
            enemy2_->SetMap(created_map);
            enemy2_->Set_Aim(hero);

            enemy3_ = new Unit::Enemy<State,Fight>(7,1,this->facade_scene);
            enemy3_->ChangeCondition(PATROUL);
            enemy3_->SetMap(created_map);

            enemy4_ = new Unit::Enemy<State,Fight>(1,5,this->facade_scene);
            enemy4_->ChangeFightCondition(DEFEND);
            enemy4_->SetMap(created_map);
}

void Field::Facade::Is_Fight(){
    if(enemy1_!=nullptr){
        enemy1_->operator+=(hero);
        hero->operator+=(enemy1_);
    }
    if(enemy1_!=nullptr){
        enemy2_->operator+=(hero);
        hero->operator+=(enemy2_);
    }
    if(enemy1_!=nullptr){
        enemy3_->operator+=(hero);
        hero->operator+=(enemy3_);
    }
    if(enemy1_!=nullptr){
        enemy4_->operator+=(hero);
        hero->operator+=(enemy4_);
    }
}

void Field::Facade::ChangeCondition(Condition *cond){
    if(this->condition){
        delete condition;
    }
    this->condition=cond;
    this->condition->setFacade(this);
}

void Field::Facade::Set_Hero_coord(int x, int y){
    this->hero_coord_x_=x;
    this->hero_coord_y_=y;
}

void Field::Facade::Set_hero_observer(Logging::HeroObserver* hero_observer){
    this->hero_observer=hero_observer;
}

void Field::Facade::Set_cell_observer(CellObserver* cell_observer){
    this->cell_observer=cell_observer;
}

void Field::Facade::Set_bridge(Logging::Bridge* bridge){
    this->bridge=bridge;
    hero -> Subscribe(bridge);
}

void Field::Facade::SetCommand(Command::Command* command){
    this->command=command;
}

void Field::Facade::Execute(){
    this->command->Execute(this->hero);
}

bool Field::Facade::IsWon(){
    return (this->hero->Is_won());
}

bool Field::Facade::Is_End_Loc(){
    return (this->hero->Is_End_Loc());
}

void Field::Facade::End_Loc(){
    int** creating_level;
    int level_2[10][10] = { {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 2, 4, 2, 2, 2, 4, 2, 2, 2},
                            {2, 2, 2, 2, 4, 2, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {0, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 2, 5, 2, 2, 2, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2, 3, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 3, 5},
                            {2, 2, 2, 2, 2, 2, 2, 2, 5, 1}};
    int fheight=10;
    int fwidth=10;

    int start_x=0;
    int start_y=0;

    creating_level= new int*[fheight];

    for(int i=0;i<fheight;i++){
        creating_level[i]= new int[fwidth];
    }

    for(int i = 0;i<fheight;i++){
        for(int j = 0;j<fheight;j++){
            creating_level[i][j]=level_2[i][j];
            if(creating_level[i][j]==0){
                start_x=j;
                start_y=i;
            }
        }
    }
    RemoveEnemies();

    created_map->Repaint(creating_level);
    if(!created_map->Get_Cell(hero_coord_x_,hero_coord_y_).Check_Enem()){
        created_map->Get_Cell(hero_coord_x_,hero_coord_y_).obj->Set_used();
    }
    hero->Set_coord(hero_coord_x_,hero_coord_y_);
    hero->Reset_Graph();
    hero->Move();
    is_dungeon=false;
}

void Field::Facade::RemoveEnemies(){
        if(enemy1_!=nullptr){
            delete enemy1_;
        }
        if(enemy2_!=nullptr){
            delete enemy2_;
        }
        if(enemy3_!=nullptr){
            delete enemy3_;
        }
        if(enemy4_!=nullptr){
            delete enemy4_;
        }
}

Unit::Hero* Field::Facade::GetHero(){
    return this->hero;
}

void Field::HeroCond::Handle(){
    this->facade->Execute();
    this->facade->Is_Fight();
    this->facade->ChangeCondition(new EnemyCond);
}

void Field::Facade::Request(){
    this->condition->Handle();
}

Field::Field* Field::Facade::GetMap(){
    return this->created_map;
}

Field::ConcreteMoment::ConcreteMoment(Facade* facade){
    this->attack=facade->GetHero()->Get_Attack();
    this->defence=facade->GetHero()->Get_Defence();
    this->coordX=facade->GetHero()->Get_coord_x();
    this->coordY=facade->GetHero()->Get_coord_y();
    this->hero_health=facade->GetHero()->Get_HP();
    this->hero_coins=facade->GetHero()->Get_Coins();
}

void Field::Facade::Restore(ConcreteMoment* mem){
    mem->SetDate(this->GetPath());
    mem->ReadFile();
    this->GetHero()->Set_coord(mem->coordX,mem->coordY);
    this->GetHero()->Set_coins(mem->hero_coins);
    this->GetHero()->SetHP(mem->hero_health);
    this->GetHero()->Set_att(mem->attack);
    this->GetHero()->Set_def(mem->defence);
    this->GetHero()->Move();
}

Field::ConcreteMoment* Field::Facade::Save(){
    ConcreteMoment* mem = new ConcreteMoment(this);
    mem->SetDate(this->GetPath());
    mem->WriteFile();
    return mem;
}

std::string Field::ConcreteMoment::date(){
    return date_;
}

void Field::ConcreteMoment::SetDate(std::string path){
    this->date_=path;
}

void Field::ConcreteMoment::ReadFile(){
    this->file_.open(date_, std::fstream::in | std::fstream::out | std::fstream::app);
    if(!file_){
        throw(FileException("Wrong file name!"));
    }else{
        file_>>this->attack;
        if(!isdigit( attack)){
            throw(FileException("Wrong data."));
        }
        if(!file_)
            throw(FileException("Data hasn't been uploaded."));
        file_>>this->defence;
        if(!isdigit( defence)){
            throw(FileException("Wrong data."));
        }
        if(!file_)
            throw(FileException("Data hasn't been uploaded."));
        file_>>this->coordX;
        if(!isdigit( coordX)){
            throw(FileException("Wrong data."));
        }
        if(!file_)
            throw(FileException("Data hasn't been uploaded."));
        file_>>this->coordY;
        if(!isdigit( coordY)){
            throw(FileException("Wrong data."));
        }
        if(!file_)
            throw(FileException("Data hasn't been uploaded."));
        file_>>this->hero_health;
        if(!isdigit( hero_health)){
            throw(FileException("Wrong data."));
        }
        if(!file_)
            throw(FileException("Data hasn't been uploaded."));
        file_>>this->hero_coins;
        if(!isdigit( hero_coins)){
            throw(FileException("Wrong data."));
        }
        if(!file_)
            throw(FileException("Data hasn't been uploaded."));
        this->file_.close();
    }
}

void Field::ConcreteMoment::WriteFile(){
    this->file_.open(date_, std::fstream::in | std::fstream::out | std::fstream::app);
    if(!file_){
        throw(FileException("Wrong file name!"));
    }else{
        file_<<this->attack<<"\n";
        if(!file_)
            throw(FileException("Data hasn't been downloaded."));
        file_<<this->defence<<"\n";
        if(!file_)
            throw(FileException("Data hasn't been downloaded."));
        file_<<this->coordX<<"\n";
        if(!file_)
            throw(FileException("Data hasn't been downloaded."));
        file_<<this->coordY<<"\n";
        if(!file_)
            throw(FileException("Data hasn't been downloaded."));
        file_<<this->hero_health<<"\n";
        if(!file_)
            throw(FileException("Data hasn't been downloaded."));
        file_<<this->hero_coins<<"\n";
        if(!file_)
            throw(FileException("Data hasn't been downloaded."));
        this->file_.close();
    }
}

void Field::ConcreteCareTaker::Undo(){
    ConcreteMoment* mem = new ConcreteMoment(facade_);
    this->SetMemento(mem);
    facade_->Restore(mementos.back());
    mementos.pop_back();
}

void Field::ConcreteCareTaker::BackUp(){
    mementos.push_back(facade_->Save());
}

void Field::ConcreteCareTaker::SetFacade(Facade* facade){
    this->facade_=facade;
}

void Field::ConcreteCareTaker::SetMemento(ConcreteMoment* mem){
    this->mementos.push_back(mem);
}
