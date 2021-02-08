#ifndef ASKLOG_H
#define ASKLOG_H

#include <QCheckBox>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>

class AskLog : public QWidget{
    Q_OBJECT
public:
    explicit AskLog(QWidget *parent = nullptr);
    QCheckBox* cb1;
    QCheckBox* cb2;
    QPushButton *ok;
signals:
    void myclose();
};

#endif // ASKLOG_H
