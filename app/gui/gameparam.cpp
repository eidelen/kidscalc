#include "gameparam.h"
#include "ui_gameparam.h"

#include <QFile>
#include <QXmlStreamWriter>

QString SettingsFileName = "params.txt";

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

void GameParam::storeParams() const
{
    QFile file(SettingsFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeTextElement("type", ui->exType->currentText());
    stream.writeTextElement("nbrOperands", QString::number(ui->nbrOps->value()));
    stream.writeTextElement("nbrExercises", QString::number(ui->nbrExercises->value()));
    stream.writeTextElement("nbrRange", QString::number(ui->nbrRangeMax->value()));
    stream.writeEndDocument();
}
