#include "solution.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>



Solution::Solution()
{

}




//check the number is in the row
bool Solution::row_check(int sudoku[9][9],const int &x,const int &number)
{
    bool NumberIsOk=true;

    for(int i=0; i<9 && NumberIsOk==true;i++){
        if(sudoku[x][i]==number) {NumberIsOk=false;}
    }

    return NumberIsOk;
}



//check the number is in the column
bool Solution::column_check(int sudoku[9][9], const int &y, const int &number)
{
    bool NumberIsOk=true;

    for(int i=0;i<9 && NumberIsOk==true;i++){
        if (sudoku[i][y]==number) {NumberIsOk=false;}
    }

    return NumberIsOk;
}




//check the number is in the 3X3 region
bool Solution::region_check(int sudoku[9][9], const int &x, const int &y, const int &number)
{
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




//check the number is in the 3X3 region
bool Solution::region_check(int sudoku[9][9],const int &row, const int &number)
{
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





//try writing numbers into the cells
bool Solution::cell_solve(int sudoku[9][9])
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
                }
            }

        }
    }

    return NumberIsOk;
}




//try writing numbers into the 3X3 regions
bool Solution::region_solve(int sudoku[9][9])
{
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
                }


            }

        }
    }

    return NumberIsOk;
}






//try writing numbers into the rows
bool Solution::row_solve(int sudoku[9][9])
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
                }

            }

        }
    }

    return NumberIsOk;
}




//try writing numbers into the columns
bool Solution::column_solve(int sudoku[9][9])
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
                }

            }

        }
    }

    return NumberIsOk;
}







// write the solution into the Solution.txt
void Solution::write_out(int sudoku[9][9])
{
    int x, y;

    std::ofstream outfile("Solution.txt");

    for(x=0;x<9;x++) {
        for(y=0;y<9;y++) {
           outfile<<sudoku[x][y]<<" ";
        }

        if(x!=8) {
            outfile<<std::endl;
        }
    }

    outfile.close();
}









//check the number is in the first 17th numbers
bool Solution::first_numbers_check( int x, int y, std::vector<std::pair<int,int>> v)
{
    bool CoordinateIsOk=true;

    for(int i=0; i<v.size() && CoordinateIsOk==true; i++){
        if(v[i].first==x && v[i].second==y){
            CoordinateIsOk=false;
        }
    }

    return CoordinateIsOk;
}




void Solution::step_back(int &x, int &y, int&y_2,int sudoku[9][9])
{
    if(y==1){
        y=8;
        --x;
        y_2=0;
    }
    else{
        if(y==0){
            y=7;
            --x;
            y_2=0;
        }
        else{
            y-=2;
        }


    }
}






std::pair<int,int> Solution::number_change(int sudoku2[9][9],  int x_2,  int y_2,  std::vector<std::pair<int,int>> v,int &m)
{
    int x, y, number;

    //step back
    if(y_2==0){
        y_2=8;
        --x_2;
    }
    else{
        y_2-=1;
    }


    //check the number is in the first 17th numbers
    if(!first_numbers_check(x_2,y_2,v)){
        if(y_2==0){
            y_2=8;
            --x_2;
        }
        else{
            y_2-=1;
        }
    }

    int c=0;



    for(x=x_2; x<9 && c==0; x++){
        for(y=y_2; y<9 && c==0; y++){

            if(first_numbers_check(x,y,v)){

                if (sudoku2[x][y]==9){

                    sudoku2[x][y]=0;
                    step_back( x, y, y_2,sudoku2);
                    m++;

                }
                else{

                    for(number=sudoku2[x][y]+1; number<10; number++){
                        if(row_check(sudoku2,x,number) && column_check(sudoku2,y,number) && region_check(sudoku2,x,y,number)){
                            sudoku2[x][y]=number;
                            x_2=x;
                            y_2=y;
                            c=1;
                            m++;
                            break;
                        }
                        else{
                            if (number==9){
                                sudoku2[x][y]=0;
                                step_back( x, y,y_2,sudoku2);
                                m++;

                            }
                        }
                    }



                }
            }
            else{
                step_back( x, y, y_2,sudoku2);
                m++;
            }


        }
    }

    return std::make_pair(x_2,y_2);
}









int Solution::backtrack(int sudoku2[9][9],std::vector<std::pair<int,int>> v)
{
    int x, y, number;
    bool CoordinateIsOk;
    std::pair<int, int> xy;
    int m=0;

    for(x=0; x<9 && m<3000; x++){
        for(y=0; y<9 && m<3000; y++){


            CoordinateIsOk=first_numbers_check(x, y, v);


            if(CoordinateIsOk==true){
                for(number=1; number<10 && m<3000; number++){
                    if(row_check(sudoku2,x,number) && column_check(sudoku2,y,number) && region_check(sudoku2,x,y,number)){
                        sudoku2[x][y]=number;
                        m++;
                        break;
                    }
                    else{
                        if (number==9){
                            xy=number_change(sudoku2,x,y,v,m);
                            x=xy.first;
                            y=xy.second;
                            break;
                        }
                    }



                }

            }


        }

    }

    return m;

}










int Solution::solve(int sudoku[9][9])
{
    std::vector<std::pair<int,int>> v;
    bool WriteNumber=true;
    int x,y,m;


    while(WriteNumber){

        if(cell_solve(sudoku) || row_solve(sudoku) || column_solve(sudoku) || region_solve(sudoku)){
            WriteNumber=true;
        }
        else{
            WriteNumber=false;
        }

    }



    for(x=0;x<9;x++) {
        for(y=0;y<9;y++) {
            sudoku2[x][y]=sudoku[x][y];
            if (sudoku[x][y]!=0){
                v.push_back(std::make_pair(x,y));
            }
        }
    }




    m=backtrack(sudoku2,v);
    write_out(sudoku2);

    return m;



}
