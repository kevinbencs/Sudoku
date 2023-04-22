#include "solution.h"
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <unistd.h>


Solution::Solution()
{

}





bool Solution::row_check(int sudoku[9][9],const int &x,const int &number)
{
    bool NumberIsOk=true;

    for(int i=0; i<9 && NumberIsOk==true;i++){
        if(sudoku[x][i]==number) {NumberIsOk=false;}
    }

    return NumberIsOk;
}




bool Solution::column_check(int sudoku[9][9], const int &y, const int &number)
{
    bool NumberIsOk=true;

    for(int i=0;i<9 && NumberIsOk==true;i++){
        if (sudoku[i][y]==number) {NumberIsOk=false;}
    }

    return NumberIsOk;
}





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




void Solution::step_back(int &x, int &y, int &m, int&y_2)
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


    if(y_2==0){
        y_2=8;
        --x_2;
    }
    else{
        y_2-=1;
    }


    // ha nem jó, mert benne van az első 17-ben, akk visszalépek
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
                    step_back( x, y, m,y_2);

                }
                else{

                    for(number=sudoku2[x][y]+1; number<10; number++){
                        if(row_check(sudoku2,x,number) && column_check(sudoku2,y,number) && region_check(sudoku2,x,y,number)){
                            sudoku2[x][y]=number;
                            x_2=x;
                            y_2=y;
                            c=1;
                            break;
                        }
                        else{
                            if (number==9){
                                sudoku2[x][y]=0;
                                step_back( x, y, m,y_2);

                            }
                        }
                    }



                }
            }
            else{
                step_back( x, y, m,y_2);
            }


        }
    }

    return std::make_pair(x_2,y_2);
}









void Solution::rand_ger(int sudoku2[9][9],std::vector<std::pair<int,int>> v)
{
    int x, y, number;
    bool CoordinateIsOk;
    std::pair<int, int> xy;
    int m=0;

    for(x=0; x<9; x++){
        for(y=0; y<9; y++){


            CoordinateIsOk=first_numbers_check(x, y, v);


            if(CoordinateIsOk==true){
                for(number=1; number<10; number++){
                    if(row_check(sudoku2,x,number) && column_check(sudoku2,y,number) && region_check(sudoku2,x,y,number)){
                        sudoku2[x][y]=number;
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


}










void Solution::solve(int sudoku[9][9])
{
    std::vector<std::pair<int,int>> v;
    bool WriteNumber=true;
    int x,y;


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




    rand_ger(sudoku2,v);
    write_out(sudoku2);




}
