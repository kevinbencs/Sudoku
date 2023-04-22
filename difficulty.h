#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QDialog>
#include "game.h"

namespace Ui {
class Difficulty;
}

class Difficulty : public QDialog
{
    Q_OBJECT

public:
    explicit Difficulty(QWidget *parent = nullptr);
    ~Difficulty();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Difficulty *ui;
};

#endif // DIFFICULTY_H
