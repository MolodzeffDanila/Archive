#include "Headers/asklog.h"

AskLog::AskLog(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *ly = new QVBoxLayout();
    ok = new QPushButton("&OK",this);
    setFixedSize(200, 300);
    cb1 = new QCheckBox("Loging to file.");
    cb2 = new QCheckBox("Loging to console.");
    ly->addWidget(cb1);
    ly->addWidget(cb2);
    ly->addWidget(ok);
    setLayout(ly);
    connect(ok, &QPushButton::clicked, [=](){
        emit myclose();
    });

}
