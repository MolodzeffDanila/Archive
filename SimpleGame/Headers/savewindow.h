#ifndef SAVEWINDOW_H
#define SAVEWINDOW_H
#include "Headers/using_libs.h"

class SaveWindow : public  QWidget{
    Q_OBJECT
public:
    explicit SaveWindow(QWidget *parent = nullptr);
    QLineEdit* path_reader;
    QPushButton *ok;
    QLabel* label;
signals:
    void my_close();
};

#endif // SAVEWINDOW_H
