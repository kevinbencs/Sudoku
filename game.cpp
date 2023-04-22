#include "game.h"
#include "ui_game.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <QTextStream>
#include <QFile>

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

}

Game::~Game()
{
    delete ui;
}





bool Game::row_check(int sudoku[9][9],const int &x,const int &number)
{
    bool NumberIsOk=true;

    for(int i=0; i<9 && NumberIsOk==true;i++){
        if(sudoku[x][i]==number) {NumberIsOk=false;}
    }

    return NumberIsOk;
}




bool Game::column_check(int sudoku[9][9], const int &y, const int &number)
{
    bool NumberIsOk=true;

    for(int i=0;i<9 && NumberIsOk==true;i++){
        if (sudoku[i][y]==number) {NumberIsOk=false;}
    }

    return NumberIsOk;
}





bool Game::region_check(int sudoku[9][9], const int &x, const int &y, const int &number)
{
    int sudoku_region[9][9]={{0,1,2,9,10,11,18,19,20},
                            {3,4,5,12,13,14,21,22,23},
                            {6,7,8,15,16,17,24,25,26},
                            {27,28,29,36,37,38,45,46,47},
                            {30,31,32,39,40,41,48,49,50},
                            {33,34,35,42,43,44,51,52,53},
                            {54,55,56,63,64,65,72,73,74},
                            {57,58,59,66,67,68,75,76,77},
                            {60,61,62,69,70,71,78,79,80}};

    bool NumberIsOk=true;
    int x_2,y_2,row;

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (sudoku_region[i][j]==x*9+y) {
                row=i;
                i=9;
                j=9;

            }

        }
    }


    for (int i=0; i<9 && NumberIsOk==true; i++) {
        x_2=sudoku_region[row][i]/9;
        y_2=sudoku_region[row][i]%9;

        if (sudoku[x_2][y_2]==number) {
            NumberIsOk=false;
        }

    }

    return NumberIsOk;
}





bool Game::region_check(int sudoku[9][9],const int &row, const int &number)
{
    int sudoku_region[9][9]={{0,1,2,9,10,11,18,19,20},
                            {3,4,5,12,13,14,21,22,23},
                            {6,7,8,15,16,17,24,25,26},
                            {27,28,29,36,37,38,45,46,47},
                            {30,31,32,39,40,41,48,49,50},
                            {33,34,35,42,43,44,51,52,53},
                            {54,55,56,63,64,65,72,73,74},
                            {57,58,59,66,67,68,75,76,77},
                            {60,61,62,69,70,71,78,79,80}};

    int x, y;
    bool NumberIsOk=true;

    for(int i=0; i<9 && NumberIsOk==true ;i++){
        x=sudoku_region[row][i]/9;
        y=sudoku_region[row][i]%9;

        if (sudoku[x][y]==number || number>9 || number<0) {
            NumberIsOk=false;
        }
    }

    return NumberIsOk;
}






bool Game::cell_solve(int sudoku[9][9],int &n)
{
    int x, y, number,x_2,y_2,NumberCounter,number2;
    bool NumberIsOk=false;


    for(x=0; x<9; x++){
        for(y=0; y<9; y++){
            NumberCounter=0;
            if (sudoku[x][y]==0){
                for(number=1; number<10 && NumberCounter<2; number++){
                    if (row_check(sudoku,x,number) && column_check(sudoku,y,number) && region_check(sudoku,x,y,number)) {
                        x_2=x;
                        y_2=y;
                        NumberCounter++;
                        number2=number;

                    }

                }
                if (NumberCounter==1){
                    sudoku[x_2][y_2]=number2;
                    NumberIsOk=true;
                    ++n;
                }
            }

        }
    }

    return NumberIsOk;
}





bool Game::region_solve(int sudoku[9][9],int &n)
{
    int sudoku_region[9][9]={{0,1,2,9,10,11,18,19,20},
                            {3,4,5,12,13,14,21,22,23},
                            {6,7,8,15,16,17,24,25,26},
                            {27,28,29,36,37,38,45,46,47},
                            {30,31,32,39,40,41,48,49,50},
                            {33,34,35,42,43,44,51,52,53},
                            {54,55,56,63,64,65,72,73,74},
                            {57,58,59,66,67,68,75,76,77},
                            {60,61,62,69,70,71,78,79,80}};

    int x, y, number, NumberCount,x_2,y_2,number2;
    bool NumberIsOk=false;

    for(int row=0; row<9; row++){
        for(number=1; number<10; number++){
            NumberCount=0;

            if (region_check(sudoku,row,number)){

                for(int i=0; i<9 && NumberCount<2; i++){
                    x=sudoku_region[row][i]/9;
                    y=sudoku_region[row][i]%9;

                    if (row_check(sudoku,x,number) && column_check(sudoku,y,number) && sudoku[x][y]==0){
                        NumberCount++;
                        x_2=x;
                        y_2=y;
                        number2=number;
                    }

                }

                if (NumberCount==1){
                    sudoku[x_2][y_2]=number2;
                    NumberIsOk=true;
                    ++n;
                }


            }

        }
    }

    return NumberIsOk;
}







bool Game::row_solve(int sudoku[9][9],int &n)
{
    int x, y, x_2, y_2, NumberCount,number,number2;
    bool NumberIsOk=false;

    for(x=0; x<9; x++){
        for(number=1; number<10; number++){
            NumberCount=0;
            if (row_check(sudoku,x,number)){
                for(y=0; y<9 && NumberCount<2; y++){

                    if(column_check(sudoku,y,number) && region_check(sudoku,x,y,number) && sudoku[x][y]==0){
                        NumberCount++;
                        x_2=x;
                        y_2=y;
                        number2=number;
                    }
                }

                if(NumberCount==1){
                    sudoku[x_2][y_2]=number2;
                    NumberIsOk=true;
                    ++n;
                }

            }

        }
    }

    return NumberIsOk;
}




bool Game::column_solve(int sudoku[9][9],int &n)
{
    int x, y, x_2, y_2, NumberCount,number,number2;
    bool NumberIsOk=false;


    for(y=0; y<9; y++){
        for(number=1; number<10; number++){
            NumberCount=0;

            if(column_check(sudoku,y,number)){

                for(x=0;x<9 && NumberCount<2; x++){

                    if (row_check(sudoku,x,number) && region_check(sudoku,x,y,number) && sudoku[x][y]==0){
                        x_2=x;
                        y_2=y;
                        NumberCount++;
                        number2=number;
                    }

                }

                if (NumberCount==1){
                    NumberIsOk=true;
                    sudoku[x_2][y_2]=number2;
                    ++n;
                }

            }

        }
    }

    return NumberIsOk;
}






void Game::copy(int sudoku[9][9],int sudoku2[9][9])
{
    int x,y;

    for(x=0;x<9;x++){
        for(y=0;y<9;y++){
            sudoku2[x][y]=sudoku[x][y];
        }
    }
}


void Game::numbers_delete(int sudoku[9][9],int delete_number)
{
    int x,y,m,n;
    srand(time(0));
    m=0;
    int sudoku2[9][9];
    bool WriteNumber;

    for(int number=1;number<delete_number; number++){
        x=rand()%9;
        y=rand()%9;

        copy(sudoku,sudoku2);


        sudoku[x][y]=0;
        m++;
        n=0;
        WriteNumber=true;

        while(WriteNumber){

            if(cell_solve(sudoku, n) || row_solve(sudoku,n) || column_solve(sudoku,n) || region_solve(sudoku,n)){
                WriteNumber=true;
            }
            else{
                WriteNumber=false;
            }

        }

        copy(sudoku2,sudoku);

        if(n!=m){
            m--;
            number-=1;
        }
        else{
            sudoku[x][y]=0;
        }



    }
}





void Game::start(int delete_number)
{
    int sudoku[9][9]={{0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0,0}};

    int sudoku_region[9][9]={{0,1,2,9,10,11,18,19,20},
                            {3,4,5,12,13,14,21,22,23},
                            {6,7,8,15,16,17,24,25,26},
                            {27,28,29,36,37,38,45,46,47},
                            {30,31,32,39,40,41,48,49,50},
                            {33,34,35,42,43,44,51,52,53},
                            {54,55,56,63,64,65,72,73,74},
                            {57,58,59,66,67,68,75,76,77},
                            {60,61,62,69,70,71,78,79,80}};



    int x,y,number,row,i,x_2,y_2;
    bool NumberIsZero,SolutionIsGood;
    Solution solution;

    srand(time(0));



    for (i = 0; i < 9; ++i) {
        ui->tableWidget->setColumnWidth(i,51);
        ui->tableWidget->setRowHeight(i,51);
    }




    i=1;


    while (i < 18) {

        NumberIsZero=true;
        x=rand()%9;
        y=rand()%9;
        number=rand()%9+1;


        if(sudoku[x][y]!=0){
            NumberIsZero=false;
        }


        for (int j = 0; j < 9; ++j) {
            if(sudoku[x][j]==number){
                NumberIsZero=false;
            }
        }


        for (int j = 0; j < 9; ++j) {
            if(sudoku[j][y]==number){
                NumberIsZero=false;
            }
        }


        for (int i = 0; i < 9; ++i) {
            for (int var = 0; var < 9; ++var) {
                if (sudoku_region[i][var]==x*9+y) {
                    row=i;
                    i=9;
                    break;
                }

            }
        }


        for (int i = 0; i < 9; ++i) {
            x_2=sudoku_region[row][i]/9;
            y_2=sudoku_region[row][i]%9;

            if (x_2!=x && y_2!=y) {
                if (sudoku[x_2][y_2]==number) {
                    NumberIsZero=false;
                    break;
                }
            }
        }



        if(NumberIsZero==true){
            sudoku[x][y]=number;
            ++i;
        }

    }

    solution.solve(sudoku);

   std::ifstream fin("Solution.txt");
    for(x=0;x<9;x++) {
        for(y=0;y<9;y++) {
            fin>>sudoku[x][y];
        }

    }
    fin.close();

    numbers_delete(sudoku,delete_number);



    ui->tableWidget->setFont(QFont("Times",15));



    for (x = 0; x < 9; ++x) {
        for (y = 0; y < 9; ++y) {
            ui->tableWidget->setItem(x,y,new QTableWidgetItem(""));
            ui->tableWidget->item(x,y)->setTextAlignment(Qt::AlignCenter);
            if (sudoku[x][y]!=0) {

                ui->tableWidget->setItem(x,y,new QTableWidgetItem(QString::number(sudoku[x][y])));
                ui->tableWidget->item(x,y)->setFont(QFont("Arial",15,900));
                ui->tableWidget->item(x,y)->setBackground(Qt::green);
                ui->tableWidget->item(x,y)->setTextAlignment(Qt::AlignCenter);



            }

        }
    }



    QFile fout("firstnumbers.txt");
    QTextStream out(&fout);

    if(!fout.open(QFile::WriteOnly)) {
        return;
    }

    for(x=0;x<9;++x){
        for(y=0;y<9;++y){
            out<<sudoku[x][y];
            out<<" ";
        }
        if(x!=8){
            out<<'\n';
        }

    }

    out.flush();
    fout.close();


}



void Game::load_saved_game()
{
    for (int i = 0; i < 9; ++i) {
        ui->tableWidget->setColumnWidth(i,51);
        ui->tableWidget->setRowHeight(i,51);
    }


    QFile fin("save.txt");
    QString str;

    QFile FirstNumbers("firstnumbers.txt");
    QString str_first_numbers;

    if(!fin.open(QFile::ReadOnly)) {
        return;
    }

    if(!FirstNumbers.open(QFile::ReadOnly)) {
        return;
    }

    QTextStream in(&fin);
    QTextStream InFirstNumbers(&FirstNumbers);

    ui->tableWidget->setFont(QFont("Times",15));
    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){
            in>>str;
            InFirstNumbers>>str_first_numbers;
            ui->tableWidget->setItem(x,y,new QTableWidgetItem(""));
            ui->tableWidget->item(x,y)->setTextAlignment(Qt::AlignCenter);
            if(str!="0"){
              ui->tableWidget->setItem(x,y,new QTableWidgetItem(str));
              ui->tableWidget->item(x,y)->setTextAlignment(Qt::AlignCenter);

              if(str==str_first_numbers){
                ui->tableWidget->item(x,y)->setBackground(Qt::green);
                ui->tableWidget->item(x,y)->setFont(QFont("Aril",15,900));
              }
            }
        }
    }

    InFirstNumbers.flush();
    FirstNumbers.close();

    in.flush();
    fin.close();
}


//new game
void Game::on_pushButton_3_clicked()
{
    this->hide();
    Difficulty difficulty;
    difficulty.setModal(true);
    difficulty.show();
    difficulty.exec();
}



//solve
void Game::on_pushButton_4_clicked()
{
    int x, y;
    int sudoku[9][9], FirstNumbers[9][9];
    std::ifstream input("Solution.txt");

    std::ifstream input_first_numbers("firstnumbers.txt");


    for(x=0;x<9;x++) {
        for(y=0;y<9;y++) {
            input>>sudoku[x][y];
            input_first_numbers>>FirstNumbers[x][y];
        }
    }




    ui->tableWidget->setFont(QFont("Times",15));
    for(x=0;x<9;x++) {
        for(y=0;y<9;y++) {
            ui->tableWidget->setItem(x,y,new QTableWidgetItem(QString::number(sudoku[x][y])));
            ui->tableWidget->item(x,y)->setTextAlignment(Qt::AlignCenter);
            if(sudoku[x][y]==FirstNumbers[x][y]){
                ui->tableWidget->item(x,y)->setFont(QFont("Arial",15,900));
                ui->tableWidget->item(x,y)->setBackground(Qt::green);
            }

            ;
        }
    }

    input.close();
    input_first_numbers.close();
}



//save
void Game::on_pushButton_2_clicked()
{
    int x,y;

    QFile fout("Save.txt");

    QString str;
    bool flag;

    if(!fout.open(QFile::WriteOnly)) {
        return;
    }

    QTextStream out(&fout);

    for(x=0;x<9;x++) {
        for(y=0;y<9;y++) {


            if (ui->tableWidget->item(x,y)) { //cell is empty return 0, else return 1
                str=ui->tableWidget->item(x,y)->text();
                if(str=="" || str==" "){
                    str="0";
                }
            }
            else {
                str="0";
            }

            out<<str+" ";


        }
        out<<'\n';
    }

    out.flush();
    fout.close();

}

//check
void Game::on_pushButton_clicked()
{
    int x,y, NumberOfNumber=0;
    QFile fin("Solution.txt");
    QString str;
    bool SolutionIsOk=true;


    if(!fin.open(QFile::ReadOnly)) {
        return;
    }

    QTextStream in(&fin);

    for(x=0;x<9 && SolutionIsOk==true;x++) {
        for(y=0;y<9 && SolutionIsOk==true;y++) {

            in>>str;

            if(ui->tableWidget->item(x,y)) {
                if(ui->tableWidget->item(x,y)->text()!="" && ui->tableWidget->item(x,y)->text()!=" "){
                    if (ui->tableWidget->item(x,y)->text()!=str) {
                        SolutionIsOk=false;
                    }
                    else{
                        NumberOfNumber++;
                    }

                }

            }

        }
    }

    if(NumberOfNumber==81 && SolutionIsOk==true){

        ui->label->setText("<p align=center><span style= font-size:22pt><b>Megoldva<b><span><p>");
    }
    else{
        if (SolutionIsOk==true) {
            ui->label->setText("<p align=center><span style= font-size:22pt><b>Eddig jó<b><span><p>");
        }
        else {
            ui->label->setText("<p align=center><span style= font-size:22pt><b>Nem jó<b><span><p>");
        }
    }



    in.flush();
    fin.close();

}


