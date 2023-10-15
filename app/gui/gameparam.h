#ifndef GAMEPARAM_H
#define GAMEPARAM_H

#include <QDialog>
#include <vector>

namespace Ui {
class GameParam;
}

class GameParam : public QDialog
{
    Q_OBJECT

public:
    explicit GameParam(QWidget *parent = nullptr);
    ~GameParam();

    enum OpType
    {
        Addition,
        Subtraction,
        Multiply,
        CSV
    };

    struct Params
    {
        OpType type;
        size_t nbrOperands;
        size_t nbrExercises;
        int nbrRange;
        QString imgDirPath;
        QString csvFilePath;
    };

    Params getGameParams() const;

    void storeParams() const;
    void loadParams();

private slots:
  void imgPathPressed();
  void csvPathPressed();

private:
    Ui::GameParam *ui;
    std::vector<std::pair<QString, OpType>> m_types;
};

#endif // GAMEPARAM_H
