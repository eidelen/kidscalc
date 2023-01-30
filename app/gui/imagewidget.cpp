#include "imagewidget.h"
#include "ui_imagewidget.h"

#include <iostream>
#include <QDir>
#include <random>

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::resetImg(QString imgDirPath)
{
    // get random image from folder
    QDir d(imgDirPath);

    if(!d.exists())
    {
        std::cout << "Dir not existing: " << imgDirPath.toStdString() << std::endl;
        return;
    }

    QFileInfoList list = d.entryInfoList(QStringList() << "*.jpg" << "*.JPG" << "*.png" << "*.PNG",
                                         QDir::Files | QDir::NoDot | QDir::NoDotAndDotDot);

    if(list.size() < 1)
    {
        std::cout << "No images in dir" << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, list.size()-1);
    QFileInfo imgFile = list.at(dist(gen));
    std::cout << "Load img: " << imgFile.absoluteFilePath().toStdString() << std::endl;
}
