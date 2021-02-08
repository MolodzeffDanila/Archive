#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Headers/field.h"
#include "Headers/using_libs.h"
#include "Headers/hero.h"
#include "Headers/facade.h"
#include "Headers/observer.h"
#include "Headers/subject.h"
#include "Headers/dialog_window.h"
#include "Headers/asklog.h"
#include "Headers/savewindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Create_ToolBar();
    void Create_StatusBar();
    void Create_Map(int num,Field::CellObserver* cell_obser);
    void Create_scene();
    void Show_Info();
    void Start_Location();
public slots:
    void Start_Game();
    void Save_Game();
    void Load_Game();
    void Dialog_log();
    void Save_log();
    void Load_log();
    void End_Game();
private slots:
    void keyPressEvent(QKeyEvent* event);
private:
    QWidget* widget;
    QGraphicsScene *scene;
    QToolBar* tool_bar;
    QGraphicsView *view;
    AskLog* dw;
    SaveWindow* sw;
    Command::UpCommand* up_cmd;
    Command::LeftCommand* left_cmd;
    Command::RightCommand* right_cmd;
    Command::DownCommand* down_cmd;
    Field::Facade* facade;
};

#endif // MAINWINDOW_H
