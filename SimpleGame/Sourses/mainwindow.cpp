#include "Headers/mainwindow.h"
#include "Headers/using_libs.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent){
    Create_scene();
    Create_ToolBar();
    Create_StatusBar();

    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout -> addWidget(view);

    widget = new QWidget(this);
    widget -> setLayout(main_layout);
    this -> setCentralWidget(widget);
    this->resize(1700, 1200);
    this->setWindowTitle("Dungeon Master: The beggining");
    up_cmd=new Command::UpCommand;
    left_cmd=new Command::LeftCommand;
    right_cmd=new Command::RightCommand;
    down_cmd=new Command::DownCommand;
}

MainWindow::~MainWindow(){
    delete up_cmd;
    delete left_cmd;
    delete down_cmd;
    delete right_cmd;
}

void MainWindow::Start_Location(){
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Enter the dungeon.","Do you like what you see?\nYou can't enter again!",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply){
        this->facade->Start_location(this->scene);
    }
}

void MainWindow::Show_Info(){
    QMessageBox::about(this,"Hero's stats",this->facade->GetHero()->Get_Info());
}

void MainWindow::Create_StatusBar(){
    this->statusBar() -> showMessage("Something");
}

void MainWindow::Create_scene(){
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/pref/resourses/desert1.jpg"));
    scene->setSceneRect(0,0,1360,1150);
}

void MainWindow::Create_ToolBar(){
    tool_bar = new QToolBar("Game options:");
    tool_bar->addAction(QIcon(":/pref/resourses/start.png"), "New Game", this, SLOT(Start_Game()));
    tool_bar->addAction(QIcon(":/pref/resourses/save1.png"), "Save Game", this, SLOT(Save_Game()));
    tool_bar->addAction(QIcon(":/pref/resourses/load1.png"), "Load Game", this, SLOT(Load_Game()));
    tool_bar->addAction(QIcon(":/pref/resourses/exit.png"), "Exit" ,this, SLOT(End_Game()));
    addToolBar(Qt::LeftToolBarArea, tool_bar);
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    if(facade && facade->GetHero()->Get_HP()<=0){
        QMessageBox::about(this,"Game over.","You died.\nHumanity is doomed because of you!\nYou'll rot here forever!");
        this->End_Game();
    }
    if(facade && facade->IsWon()){
        QMessageBox::about(this,"Finish","Level is over.\nYou've won!");
        this->End_Game();
    }
    if( (event->key() == Qt::Key_F) && (facade->GetHero()->Get_curr().obj->get_type_of_cell()==4)){
            if(facade->GetMap()->Get_Cell(facade->GetHero()->Get_coord_x(),facade->GetHero()->Get_coord_y()).obj->Is_used()){
                Start_Location();
    }
    }else if( event->key() == Qt::Key_W ){
            facade->SetCommand(up_cmd);
            facade->Request();
            facade->Request();
    }else if( event->key() == Qt::Key_A ){
            facade->SetCommand(left_cmd);
            facade->Request();
            facade->Request();
    }else if( event->key() == Qt::Key_D ){
           facade->SetCommand(right_cmd);
           facade->Request();
           facade->Request();
    }else if( event->key() == Qt::Key_S ){
        facade->SetCommand(down_cmd);
        facade->Request();
        facade->Request();
    }else if( event->key() == Qt::Key_Space){
            facade->ChangeCondition(new Field::EnemyCond);
            facade->Request();
    }else if( event->key() == Qt::Key_I ){
        Show_Info();
    }
    if(facade && facade->Is_End_Loc()){
        QMessageBox::about(this,"Finish","You destroyed forces of darnkness in that cave.\nTime to get up!");
        facade->End_Loc();
    }
}

void MainWindow::Start_Game(){
    dw = new AskLog;
    dw->show();
    connect(dw, &AskLog::myclose,this,&MainWindow::Dialog_log);
}

void MainWindow::Save_Game(){
    sw = new SaveWindow;
    sw->show();
    connect(sw, &SaveWindow::my_close,this,&MainWindow::Save_log);
}

void MainWindow::Load_Game(){
    sw = new SaveWindow;
    sw->setWindowTitle("Loading file");
    sw->show();
    connect(sw, &SaveWindow::my_close,this,&MainWindow::Load_log);
}

void MainWindow::Save_log(){
    std::string tmp(sw->path_reader->text().toStdString());
    this->facade->SetPath(tmp);
    statusBar()->showMessage(QString::fromStdString(tmp));
    facade->care_taker = new Field::ConcreteCareTaker();
    facade->care_taker->SetFacade(facade);
    facade->care_taker->BackUp();
    sw->close();
    delete sw;
}

void MainWindow::Load_log(){
    std::string tmp(sw->path_reader->text().toStdString());
    this->facade->SetPath(tmp);
    statusBar()->showMessage(QString::fromStdString(tmp));
    facade->care_taker = new Field::ConcreteCareTaker();
    facade->care_taker->SetFacade(facade);
    facade->care_taker->Undo();
    sw->close();
    delete sw;
}

void MainWindow::Dialog_log(){
    Logging::HeroObserver* hero_observer=new Logging::HeroObserver(dw->cb1->isChecked(),dw->cb2->isChecked());
    Logging::Bridge* bridge = new Logging::Bridge(hero_observer);
    Field::CellObserver* cell_observer = new Field::CellObserver(dw->cb1->isChecked(),dw->cb2->isChecked());
    facade = new Field::Facade(this-> scene,1,cell_observer);
    facade->Set_bridge(bridge);
    facade->Set_hero_observer(hero_observer);
    dw->close();
}

void MainWindow::End_Game(){
    this->close();
}






