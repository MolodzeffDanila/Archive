#include "Headers/savewindow.h"

SaveWindow::SaveWindow(QWidget* parent) : QWidget(parent){
    QVBoxLayout *ly = new QVBoxLayout();
    ok = new QPushButton("&OK",this);
    setFixedSize(300, 200);
    path_reader = new QLineEdit();
    this->setWindowTitle("Saving game.");
    label = new QLabel();
    label->setText("Enter the filename:");
    ly->addWidget(label);
    ly->addWidget(path_reader);
    ly->addWidget(ok);
    setLayout(ly);
    connect(ok, &QPushButton::clicked, [=](){
        emit my_close();
    });
}
