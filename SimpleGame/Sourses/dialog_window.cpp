#include "Headers/dialog_window.h"

Dialog_Window::Dialog_Window(QWidget* parent): QWidget(parent){
  Label = new QLabel("Choose method of logs.");
  file_checkbox=new QCheckBox(this);
  console_checkbox=new QCheckBox(this);

  okButton = new QPushButton("&Ok");
  okButton -> setEnabled(true);
  QHBoxLayout* buttonLayout = new QHBoxLayout;
  buttonLayout -> addWidget(okButton);

  connect(okButton, &QPushButton::clicked,[=](){
      if(file_checkbox->isChecked()){
          emit CheckBox1();
      }
      if(console_checkbox->isChecked()){
          emit CheckBox2();
      }
      this->close();
  });
  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout -> addWidget(file_checkbox);
  mainLayout -> addWidget(console_checkbox);
  mainLayout -> addLayout(buttonLayout);
  setLayout(mainLayout);
}

Dialog_Window::~Dialog_Window(){}
