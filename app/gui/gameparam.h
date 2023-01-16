#ifndef GAMEPARAM_H
#define GAMEPARAM_H

#include <QDialog>

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
        Subtraction
    };

    struct Params
    {
        OpType type;
        size_t nbrOperands;
        size_t nbrExercises;
        int nbrRange;
    };

    Params getGameParams() const;

    void storeParams() const;



private:
    Ui::GameParam *ui;
};

#endif // GAMEPARAM_H
