#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H
#include "Headers/using_libs.h"

class Dialog_Window: public QWidget{
    Q_OBJECT
private:
    QCheckBox* file_checkbox;
    QCheckBox* console_checkbox;
    QLabel* Label;
    QPushButton* okButton;
signals:
    void CheckBox1();
    void CheckBox2();
public:
    Dialog_Window(QWidget* parent=nullptr);
    int Get_level_number();
    ~Dialog_Window();
};

#endif // DIALOG_WINDOW_H
