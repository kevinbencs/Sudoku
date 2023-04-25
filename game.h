#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include "solution.h"
#include "difficulty.h"


namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    void start(int delete_numbers);
    void load_saved_game();


private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();




private:
    Ui::Game *ui;



    bool row_check(int sudoku[9][9],const int &x,const int &number);
    bool column_check(int sudoku[9][9], const int &y, const int &number);
    bool region_check(int sudoku[9][9], const int &x, const int &y, const int &number);
    bool region_check(int sudoku[9][9],const int &row, const int &number);

    bool cell_solve(int sudoku[9][9], int &n);
    bool region_solve(int sudoku[9][9], int &n);
    bool column_solve(int sudoku[9][9], int &n);
    bool row_solve(int sudoku[9][9], int &n);

    void copy(int sudoku[9][9],int sudoku2[9][9]);
    void numbers_delete(int sudoku[9][9], int delete_numbers);

};

#endif // GAME_H
