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

GameParam::Params GameParam::getGameParams() const
{
    Params retParams;
    QString typeText = ui->exType->currentText();
    if(typeText == "Addition")
        retParams.type = OpType::Addition;
    else
        retParams.type = OpType::Subtraction;

    retParams.nbrOperands = ui->nbrOps->value();
    retParams.nbrExercises = ui->nbrExercises->value();
    retParams.nbrRange = ui->nbrRangeMax->value();

    return retParams;
}
