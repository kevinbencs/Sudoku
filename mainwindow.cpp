#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->hide();
    Difficulty difficulty;
    difficulty.setModal(true);
    difficulty.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    Game game;
    game.setModal(true);
    game.load_saved_game();
    game.show();
    game.exec();
}

