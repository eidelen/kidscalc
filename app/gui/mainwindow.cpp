#include <iostream>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn0, &QPushButton::released, this, [this]{ numericPressed(0); });
    connect(ui->btn1, &QPushButton::released, this, [this]{ numericPressed(1); });
    connect(ui->btn2, &QPushButton::released, this, [this]{ numericPressed(2); });
    connect(ui->btn3, &QPushButton::released, this, [this]{ numericPressed(3); });
    connect(ui->btn4, &QPushButton::released, this, [this]{ numericPressed(4); });
    connect(ui->btn5, &QPushButton::released, this, [this]{ numericPressed(5); });
    connect(ui->btn6, &QPushButton::released, this, [this]{ numericPressed(6); });
    connect(ui->btn7, &QPushButton::released, this, [this]{ numericPressed(7); });
    connect(ui->btn8, &QPushButton::released, this, [this]{ numericPressed(8); });
    connect(ui->btn9, &QPushButton::released, this, [this]{ numericPressed(9); });

    connect(ui->btnDel, &QPushButton::released, this, [this]{ deletePressed(); });
    connect(ui->btnGo, &QPushButton::released, this, [this]{ goPressed(); });

    m_QuestionFactory = std::shared_ptr<SumFactory>(new SumFactory({0, 9}, 2));
    m_Play = std::shared_ptr<Play>(new Play(3, m_QuestionFactory));

    showNextQuestion();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numericPressed(int n)
{
    std::cout << "Button pressed " << n << std::endl;

    QString currentText = ui->resEdit->text();
    currentText.append(QString::number(n));
    ui->resEdit->setText(currentText);

    std::cout << "Current number: " << currentText.toStdString() << std::endl;
}

void MainWindow::goPressed()
{
    std::cout << "Go pressed" << std::endl;
    showNextQuestion();
}

void MainWindow::deletePressed()
{
    std::cout << "Delete pressed" << std::endl;
    ui->resEdit->setText("");
}

void MainWindow::showNextQuestion()
{
    std::shared_ptr<Question> q = m_Play->nextQuestion();
    if( q.get() != nullptr )
    {
        QString qText = QString::fromStdString(q->toString()) + " = ";
        ui->qLabel->setText(qText);
    }
}

