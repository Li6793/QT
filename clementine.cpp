#include "clementine.h"
#include "./ui_clementine.h"

Clementine::Clementine(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Clementine)
{
    ui->setupUi(this);
}

Clementine::~Clementine()
{
    delete ui;
}
