#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "play.h"
#include "question.h"
#include "gameparam.h"
#include "imagewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showNextQuestion();
    void newGame(GameParam::Params params);
    void endGame();
    void updateProgress();

private slots:
  void numericPressed(int n);
  void goPressed();
  void deletePressed();
  void newGamePressed();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QuestionFactory> m_QuestionFactory;
    std::shared_ptr<Play> m_Play;
    QString m_outputText;
    std::shared_ptr<Question> m_question;
    std::shared_ptr<ImageWidget> m_imgWidget;


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
