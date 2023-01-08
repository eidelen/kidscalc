#include <iostream>

#include <QDialog>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gameparam.h"

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
    connect(ui->newGameBtn, &QPushButton::released, this, [this]{ newGamePressed(); });

    newGame();
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

    if( m_question.get() == nullptr )
    {
        std::cout << "No question" << std::endl;
        return;
    }

    std::string answer = ui->resEdit->text().toStdString();
    if(answer == "")
    {
        std::cout << "No input" << std::endl;
        return;
    }

    m_question->parseAnswer(answer);

    QString resText = QString::fromStdString(m_question->toString()) + " = " + ui->resEdit->text();

    if( m_question->isCorrect() )
    {
        std::cout << " 😍" << std::endl << std::endl;
        m_outputText.append(resText + "  😍" + "\n");
    }
    else
    {
        std::cout << " 🤨 " << "The correct answer is " << m_question->getRightAnswer() << std::endl << std::endl;
        m_outputText.append(resText + "  🤨 (" + QString::fromStdString(m_question->getRightAnswer()) + ")\n");
    }

    ui->outputPanel->setText(m_outputText);

    updateProgress();

    showNextQuestion();
}

void MainWindow::deletePressed()
{
    std::cout << "Delete pressed" << std::endl;
    ui->resEdit->setText("");
}

void MainWindow::newGamePressed()
{
    GameParam* paramDialog = new GameParam();
    paramDialog->exec();
    delete paramDialog;

    newGame();
}

void MainWindow::showNextQuestion()
{
    ui->resEdit->setText("");

    m_question = m_Play->nextQuestion();
    if( m_question.get() != nullptr )
    {
        QString qText = QString::fromStdString(m_question->toString()) + " = ";
        ui->qLabel->setText(qText);
    }
    else
    {
        endGame();
    }
}

void MainWindow::newGame()
{
    m_outputText = "";
    ui->outputPanel->setText(m_outputText);
    ui->resEdit->setText("");

    m_QuestionFactory = std::shared_ptr<SumFactory>(new SumFactory({0, 5}, 2));
    m_Play = std::shared_ptr<Play>(new Play(5, m_QuestionFactory));

    ui->progressBar->setRange(0, m_Play->getNumberOfQuestions());

    showNextQuestion();

    updateProgress();
}

void MainWindow::endGame()
{
    auto[right, wrong, answered, unanswered, successRate] = m_Play->getStat();
    QString performance = QString::number(right) + " right, " + QString::number(wrong) + " wrong \n";

    if(successRate > 0.9999)
    {
        performance.append("🏆🏆🏆🏆🏆🏆🏆🏆");
    }
    else if(successRate > 0.7999)
    {
        performance.append("🥰🥰🥰");
    }
    else if(successRate > 0.4999)
    {
        performance.append("👌👌");
    }
    else if(successRate > 0.1999)
    {
        performance.append("🐈");
    }
    else
    {
        performance.append("🙈");
    }

    m_outputText.append(performance);
    ui->outputPanel->setText(m_outputText);
}

void MainWindow::updateProgress()
{
    auto[right, wrong, answered, unanswered, successRate] = m_Play->getStat();
    ui->progressBar->setValue(answered);
}

