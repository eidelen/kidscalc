#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "play.h"
#include "question.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


// only for fast testing
class SumFactory : public QuestionFactory
{
public:
    SumFactory(std::pair<int,int> numberRange, size_t length): QuestionFactory()
    {
        m_numberRange = numberRange;
        m_length = length;
    }

    ~SumFactory()
    {
    }

    std::shared_ptr<Question> createQuestion() override
    {
        return std::shared_ptr<Question>(new SumQuestion(m_numberRange, m_length) );
    }

    std::pair<int,int> m_numberRange;
    size_t m_length;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showNextQuestion();
    void newGame();
    void endGame();

private slots:
  void numericPressed(int n);
  void goPressed();
  void deletePressed();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QuestionFactory> m_QuestionFactory;
    std::shared_ptr<Play> m_Play;
    QString m_outputText;
    std::shared_ptr<Question> m_question;
};
#endif // MAINWINDOW_H
