#include "gameparam.h"
#include "ui_gameparam.h"

#include <iostream>

#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

QString SettingsFileName = "params.txt";

GameParam::GameParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameParam)
{
    ui->setupUi(this);
    loadParams();
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

    stream.writeStartElement("params");

    stream.writeTextElement("type", ui->exType->currentText());
    stream.writeTextElement("nbrOperands", QString::number(ui->nbrOps->value()));
    stream.writeTextElement("nbrExercises", QString::number(ui->nbrExercises->value()));
    stream.writeTextElement("nbrRange", QString::number(ui->nbrRangeMax->value()));

    stream.writeEndElement();

    stream.writeEndDocument();
}

void GameParam::loadParams()
{
    QFile file(SettingsFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "No settings file" << std::endl;
        return;
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd())
    {
        xml.readNext();

        if(xml.isStartElement())
        {
            QString tagName = xml.name().toString();
            if(tagName == "type")
            {
                QString opsName = xml.readElementText();
                if(opsName == "Addition")
                    ui->exType->setCurrentIndex(0);
                else if(opsName == "Subtraction")
                    ui->exType->setCurrentIndex(1);
            }
            else if(tagName == "nbrOperands")
            {
                ui->nbrOps->setValue( xml.readElementText().toInt());
            }
            else if(tagName == "nbrExercises")
            {
                ui->nbrExercises->setValue( xml.readElementText().toInt());
            }
            else if(tagName == "nbrRange")
            {
                ui->nbrRangeMax->setValue( xml.readElementText().toInt());
            }
        }
    }

    if (xml.hasError())
    {
        std::cout << "Error in xml file" << std::endl;
    }
}
