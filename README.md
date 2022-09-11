# Sudoku Solver
More information about the backtracking algorithm can be found [here](https://en.wikipedia.org/wiki/Sudoku_solving_algorithms)
        
### Required packages

This project uses only the C++ Standard Library.

### Compilation
        g++ -std=c++11 SudokuSolver.cpp -o sudoku
        ./sudoku < filename
Where 'filename' is the name of the txt file with the incomplete sudoku board. An example is provided in example.txt

## General Backtracking Algorithm:
1. Find the next zero and "select" that number
2. Increment the "selected" number
3. Check if the placement of the number is valid by checking the row, column, and box
4. If valid, go back to step 1
5. If not valid, go back to step 2 until 9 is reached
6. If 9 is not valid, set the current value to zero, return to the previous number placed on the grid,
increment it, and return to step 3

## Issues while creating the program:
### Speed of the algorithm:
I had originally had many nested loops in order to create the logic for incrementing and subsequently checking the validity of the number placements. I had a while loop with a flag for if the number placement was valid. Once a valid placement was found, the loop continued to keep checking the columns anyway, because no exit condition was set. This worked, because the while loop had a header that broke as soon as the program was finished looping through the column, but was not as efficient until I included an if statement after checking the row validity.
        if (validPlacementRow == false) {
            continue;
        }
Which would instantly continue to the next iteration in the while loop, which in this case was incrementing the selected number again.


### Readability:
After creating the main logic for the algorithm, I found that my code was not easy to follow. I started to create functions for repeated tasks to make the program more readable.
Including findNextZero and findValidNum

### Algorithm for findValidNum:
Compares selectedNum to each value in row first. If no match is found, it compares selectedNum to each value in the column. If no match is found, it compares selectedNum to each value in the box. If a match is found at any point, selectedNum is incremented and the process repeats until a number is found with no matches or 9 is reached.

This function went through many iterations, and it took me a few hours to settle on this version. It is clean, simple, and relatively fast.

### Backtracking:
The most difficult part of the algorithm was managing all of the variables necessary to backtrack. After brainstorming some possibilities and trying some in practice, I settled on this: 

If backtracking is necessary for the current iteration (which is if selectedNum is 0 after running findValidNum), then...

1. Store the current grid index in indexHolder to return to once we are done backtracking
2. Use a while loop to loop thru steps 3-6 until selectedNum is not zero
3. Keep track of the number of times this process is done with backtrackCount so that we do not store indexes which are already stored in indexHolder. Essentially we are using backtrackCount to “catch up” after backtracking (this is done with a simple if statement)
4. Return to the previous index in indexHolder and store the index in selectedIndex and value in selectedNum
5. Use findValidNum to find a valid number for the previous index that is now selected
6. Update the number in the grid

This version of backtracking which updates the grid position to be zero whenever backtracking is necessary means that I could still use the code I wrote in findNextZero, and I would not have to write new code for the “catching up” part. This is because the catching up part is the same as the process of looping through the grid since indexes which do not have a valid number are reset to zero before backtracking.


### Printing the grid and steps:
A straightforward block of code, print the grid whenever a change is made. The only issue I had with it was figuring out a way to print out that the algorithm had tried and failed to find a valid number, and must now backtrack to the previous index. I decided on what you see now. It makes more sense to me for the program to output one time that it has failed to find a valid number, and simply print the index it backtracks to until it finds a valid number, at which time it updates the grid and prints it. This allows the program to backtrack two times or twenty times, but only take up four lines in the console. All the while printing the indexes it attempted to find valid numbers for.

For example:

...\
NO VALID NUMBER AT: [4, 6]\
BACKTRACKING… [4, 2]\
BACKTRACKING… [4, 1]

STEP 742\
Index Modified: [4, 1]\
Backtrack Count: 21\
Current Index in Holder: 22\
*updated grid not shown*\
...
