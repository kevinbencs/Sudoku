#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>



class Solution
{

public:
    Solution();
    int solve(int sudoku[9][9]);

private:
    bool row_check(int sudoku[9][9], const int &x, const int &number);
    bool column_check(int sudoku[9][9],const int &y, const int &number);
    bool region_check(int sudoku[9][9], const int &x, const int &y, const int &number);
    bool region_check(int sudoku[9][9], const int &row, const int &number);

    bool cell_solve(int sudoku[9][9]);
    bool row_solve(int sudoku[9][9]);
    bool column_solve(int sudoku[9][9]);
    bool region_solve(int sudoku[9][9]);

    int backtrack(int sudoku2[9][9], std::vector<std::pair<int, int> > v);
    std::pair<int,int> number_change(int sudoku[9][9], int x_2, int y_2, std::vector<std::pair<int,int>> v, int &m);
    bool first_numbers_check( int x, int y, std::vector<std::pair<int,int>> v);


    void write_out(int sudoku[9][9]);
    void step_back(int &x, int &y, int &y_2, int sudoku[9][9]);

    int sudoku_region[9][9]={{0,1,2,9,10,11,18,19,20},
                            {3,4,5,12,13,14,21,22,23},
                            {6,7,8,15,16,17,24,25,26},
                            {27,28,29,36,37,38,45,46,47},
                            {30,31,32,39,40,41,48,49,50},
                            {33,34,35,42,43,44,51,52,53},
                            {54,55,56,63,64,65,72,73,74},
                            {57,58,59,66,67,68,75,76,77},
                            {60,61,62,69,70,71,78,79,80}};

    int sudoku2[9][9];




};

#endif // SOLUTION_H
