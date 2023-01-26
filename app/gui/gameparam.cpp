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

    m_types.push_back({"Addition", OpType::Addition});
    m_types.push_back({"Subtraction", OpType::Subtraction});

    // add operations to dropdown
    for(auto& [typeQStr, typeId] : m_types)
        ui->exType->addItem(typeQStr);

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
    auto selectedType = std::find_if(m_types.begin(), m_types.end(), [&typeText](const std::pair<QString, OpType>& e) {
        return typeText == e.first;
    });
    // default addition
    retParams.type = selectedType == m_types.end() ? OpType::Addition : (*selectedType).second;

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

                auto foundType = std::find_if(m_types.begin(), m_types.end(), [&opsName](const std::pair<QString, OpType>& e) {
                    return opsName == e.first;
                });

                int selectedIdx = foundType == m_types.end() ? 0 : std::distance(m_types.begin(), foundType);
                ui->exType->setCurrentIndex(selectedIdx);
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
