#include "difficulty.h"
#include "ui_difficulty.h"
#include "ctime"
#include <cstdlib>

Difficulty::Difficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Difficulty)
{
    ui->setupUi(this);
}

Difficulty::~Difficulty()
{
    delete ui;
}

//Easy
void Difficulty::on_pushButton_clicked()
{
    int delete_number;

    srand(time(0));
    delete_number=rand()%10+30;

    this->hide();
    Game game;
    game.setModal(true);
    game.start(delete_number);
    game.show();
    game.exec();




}

//Medium
void Difficulty::on_pushButton_2_clicked()
{
    int delete_number;

    srand(time(0));
    delete_number=rand()%10+40;

    this->hide();
    Game game;
    game.setModal(true);
    game.start(delete_number);
    game.show();
    game.exec();
}

//Hard
void Difficulty::on_pushButton_3_clicked()
{
    int delete_number;

    srand(time(0));
    delete_number=rand()%10+50;

    this->hide();
    Game game;
    game.setModal(true);
    game.start(delete_number);
    game.show();
    game.exec();
}

