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

private:
    Ui::GameParam *ui;
};

#endif // GAMEPARAM_H
