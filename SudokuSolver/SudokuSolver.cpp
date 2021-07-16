//
//--SUDOKU SOLVER BY BACKTRACKING--

//algorithm:
//1. find the next zero and "select" that number
//2. increment the "selected" number
//3. check if the placement of the number is valid by checking the row and column
//4. if valid, go back to step 1
//5. if not valid, go back to step 2 until 9 is reached
//6. if 9 is not valid, set the current value to zero, return to the previous number placed on the grid,
//increment it, and return to step 3

#include <iostream>
#include <vector>

using namespace std;

struct zeroIndex { int row,col; };

void printGrid(int grid[9][9]);
zeroIndex findNextZero(int grid[9][9]);
int findValidNum(zeroIndex selectedIndex, int selectedNum, 
    vector< pair<int, int> > indexHolder, int grid[9][9]);


int main()
{
    
    int selectedNum;
    // int boxNum;
    bool foundZero = false;
    bool validPlacement = true;
    zeroIndex selectedIndex;
    vector< pair<int, int> > indexHolder;

    // make the grid global so everywhere can modify it? 
    int grid[9][9] = { {3, 0, 6, 5, 0, 8, 4, 0, 0},
         {5, 2, 0, 0, 0, 0, 0, 0, 0},
         {0, 8, 7, 0, 0, 0, 0, 3, 1},
         {0, 0, 3, 0, 1, 0, 0, 8, 0},
         {9, 0, 0, 8, 6, 3, 0, 0, 5},
         {0, 5, 0, 0, 9, 0, 6, 0, 0},
         {1, 3, 0, 0, 0, 0, 2, 5, 0},
         {0, 0, 0, 0, 0, 0, 0, 7, 4},
         {0, 0, 5, 2, 0, 6, 3, 0, 0} };

    // print the original array
    printGrid(grid);




    // keep repeating the algorithm until there are no more zeroes in the grid
    while (findNextZero(grid).row != -1) {

        // find the next zero index and "select" it
        selectedIndex = findNextZero(grid);

        // store the value at the selected index
        selectedNum = grid[selectedIndex.row][selectedIndex.col];

        cout << "Next zero index at [" << selectedIndex.row << ", " << selectedIndex.col << "]\n";


        // store the index so we can return to it if necessary to backtrack
        indexHolder.push_back(make_pair(selectedIndex.row, selectedIndex.col));

        // find the next valid number 1-9 for the selected index
        selectedNum = findValidNum(selectedIndex, selectedNum, indexHolder, grid);

        // place the valid number into the grid
        grid[selectedIndex.row][selectedIndex.col] = selectedNum;



        printGrid(grid);


    }
    return 0;
}


int backtrack(zeroIndex selectedIndex, int selectedNum,
    vector< pair<int, int> > indexHolder, int grid[9][9]) 
{
    

    return -1;
}

zeroIndex findNextZero(int grid[9][9]) {
    // find the next zero index
    // selectedIndex is set to { -1,-1 } because that is returned if no zeroes are left
    zeroIndex selectedIndex = { -1,-1 };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                selectedIndex.row = i;
                selectedIndex.col = j;
                return selectedIndex;
            }
        }
    }

    return selectedIndex;
}

int findValidNum(zeroIndex selectedIndex, int selectedNum, 
    vector< pair<int, int> > indexHolder, int grid[9][9]) 
{

    bool validPlacement = true;
    int boxRow = selectedIndex.row / 3;
    int boxCol = selectedIndex.col / 3;

    // increment selected number and loop it through 1 to 9 and check if the placement is valid each time
    while (selectedNum < 9) {
        selectedNum++;
        validPlacement = true;

        // check if number placement is valid in row
        for (int i = 0; i < 9; i++) {
            // skip over the row of the selected number
            if (i == selectedIndex.col) {
                continue;
            }

            // if current number equals selected number, set valid flag to false
            if (grid[selectedIndex.row][i] == selectedNum) {
                validPlacement = false;
                break;
            }

        }

        // if the placement is marked as invalid for the row, don't bother checking
        // the columns, just move on to the next number 1-9
        if (validPlacement == false) {
            continue;
        }

        // check if number placement is valid in column
        for (int j = 0; j < 9; j++) {
            // skip over the column of the selected number
            if (j == selectedIndex.row) {
                continue;
            }

            // if current number equals selected number, set valid flag to false
            if (grid[j][selectedIndex.col] == selectedNum) {
                validPlacement = false;
                break;
            }

        }

        // if the placement is marked as invalid for the column, don't bother checking
        // the box, just move on to the next number 1-9
        if (validPlacement == false) {
            continue;
        }


        // check if number placement is valid in box by looping through 
        // (boxRow,boxCol) to (boxRow+2,boxCol+2)
        for (int i = boxRow; i < (boxRow + 3); i++) {
            for (int j = boxCol; j < (boxCol + 3); j++) {
                // skip over selectedIndex
                if ((i == selectedIndex.row) && (j == selectedIndex.col)) {
                    continue;
                }

                // if current number equals selected number, set valid flag to false
                if (grid[i][j] == selectedNum) {
                    validPlacement = false;
                }
            }
        }



        // if the entire row, column, and box have been checked and the number is still valid, 
        // you've found a valid number
        if (validPlacement) {
            return selectedNum;
        }

    }
    
    // this part is only reached if 9 is not valid,
    // should I backtrack here or in main? or in another function? 
    // i need a way to
    // 1. go back to the previous index and call findValidNum again
    // 2. update grid correctly with the valid number found, or backtrack again if necessary
    // 


}

void printGrid(int grid[9][9]) {

    for (int i = 0; i < 9; i++) {
        cout << "{";
        for (int j = 0; j < 9; j++) {
            if (j == 8) {
                cout << grid[i][j];
                continue;
            }
            cout << grid[i][j] << ", ";
        }
        cout << "}" << endl;
    }
}

