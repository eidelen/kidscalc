#include <iostream>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn4, &QPushButton::released, this, [this]{ handleButtonPress(4); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonPress(int n)
{
    std::cout << "Button pressed " << n << std::endl;
}

