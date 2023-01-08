#include "gameparam.h"
#include "ui_gameparam.h"

GameParam::GameParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameParam)
{
    ui->setupUi(this);
}

GameParam::~GameParam()
{
    delete ui;
}
