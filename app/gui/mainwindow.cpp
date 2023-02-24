#include <iostream>

#include <QDialog>
#include <QKeyEvent>
#include <QIntValidator>

#include "factories.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"


class HCQuestionFactory : public QuestionFactory
{
public:
    HCQuestionFactory(std::vector<std::pair<std::string,std::string>> questions): QuestionFactory(),
        m_idx(0), m_questions(questions)
    {
    }

    ~HCQuestionFactory()
    {
    }

    std::shared_ptr<Question> createQuestion() override
    {
        if(m_idx >= m_questions.size())
            m_idx = 0;

        std::shared_ptr<HardcodedQuestions> q(new HardcodedQuestions(m_questions.at(m_idx).first, m_questions.at(m_idx).second));

        m_idx++;
        return q;
    }

    size_t m_idx;
    std::vector<std::pair<std::string,std::string>> m_questions;
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_imgWidget = std::shared_ptr<ImageWidget>(new ImageWidget());

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
    //connect(ui->newGameBtn, &QPushButton::released, this, [this]{ newGamePressed(); });

    GameParam::Params fakeParams;
    newGame(fakeParams);
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
        m_outputText.append(resText + "  🤨 "); // + QString::fromStdString(m_question->getRightAnswer()) + ")\n");
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
    if(paramDialog->exec() == QDialog::Accepted)
    {
        GameParam::Params params = paramDialog->getGameParams();
        newGame(params);
        paramDialog->storeParams();
    }

    delete paramDialog;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        goPressed();
    }
    else if(event->key() == Qt::Key_N)
    {
        newGamePressed();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_imgWidget->close();
    event->accept();
}

void MainWindow::showNextQuestion()
{
    ui->resEdit->setText("");

    m_question = m_Play->nextQuestion();
    if( m_question.get() != nullptr )
    {
        QString qText = QString::fromStdString(m_question->toString()) ;
        ui->qLabel->setText(qText);
    }
    else
    {
        endGame();
    }
}

void MainWindow::newGame(GameParam::Params /*params*/)
{
    m_outputText = "";
    ui->outputPanel->setText(m_outputText);
    ui->resEdit->setText("");

    /*
    if(params.type == GameParam::Addition)
    {
        m_QuestionFactory = std::shared_ptr<SumFactory>(new SumFactory({0, params.nbrRange}, params.nbrOperands));
    }
    else
    {
        m_QuestionFactory = std::shared_ptr<SubFactory>(new SubFactory({0, params.nbrRange}, params.nbrOperands));
    }*/

    std::vector<std::pair<std::string, std::string>> qs = {
        {"ANIC: Der beste Kindergarten in Thun?", "Seefeld"},
        {"SOHYI: Grosser Fels, welcher um die Erde kreist?", "Mond"},
        {"AINA: Wie alt wird Carla?", "5"},
        {"JARA: Das älteste Gebäude in Thun?", "Schloss"},
        {"ELLA: Der beste Koch auf der Welt?", "Stefan"},
        {"MIRO: Der beste Sport mit einem Ball?", "Fussball"},
        {"CARLA: Ein guter Freund auf 4 Beinen?", "Herr Boggen"},
        {"NARI: Ein schleimiger Fresshund?", "Juku"},
        {"Ädu: Dritte Wurzel aus 1367631?", "111"}
    };
    m_QuestionFactory = std::shared_ptr<HCQuestionFactory>(new HCQuestionFactory(qs));

    m_Play = std::shared_ptr<Play>(new Play(qs.size(), m_QuestionFactory));

    ui->progressBar->setRange(0, m_Play->getNumberOfQuestions());


    m_imgWidget->show();
    m_imgWidget->resetImg("/Users/eidelen/Downloads/carla");


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

    double currentImgQuality = ((double)right)/m_Play->getNumberOfQuestions();

    // enhance slowely!
    currentImgQuality = std::pow(currentImgQuality, 3);

    m_imgWidget->updateQuality(currentImgQuality);
}

