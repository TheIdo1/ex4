/******************
Name: Ido Itzhak
ID: 69420
Assignment: Ex4
*******************/

#include <stdio.h>
#include <string.h>

#define CHEERLEADERS_ROWS 5
#define CHEERLEADERS_COLUMNS 5
#define MAX_GRID_SIZE_QUEENS 20
#define MAX_GRID_SIZE_CROSSWORD 30
#define MAX_INPUTS_CROSSWORD 100
#define MAX_WORD_LENGTH 16

typedef struct CrosswordSkeleton {
    int row;
    int column;
    int length;
    char direction;
    char word[MAX_WORD_LENGTH];
    int occupied;
} CrosswordSkeleton;

int task1RobotPaths(int column, int row);

float task2HumanPyramid(float weights[CHEERLEADERS_ROWS][CHEERLEADERS_COLUMNS], int rows, int columns, int currentRow,
                        int currentColumn);

int task3ParenthesisValidator(char lookFor);

int task4QueensBattle(char board[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int columns[MAX_GRID_SIZE_QUEENS],
                      int rows[MAX_GRID_SIZE_QUEENS], char colors[MAX_GRID_SIZE_QUEENS],
                      int queens[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int size, int x, int y);

int tryPlaceQueen(char board[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int columns[MAX_GRID_SIZE_QUEENS],
                  int rows[MAX_GRID_SIZE_QUEENS], char colors[MAX_GRID_SIZE_QUEENS],
                  int queens[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int size, int x, int y);

void tryRemoveQueen(int columns[MAX_GRID_SIZE_QUEENS], int rows[MAX_GRID_SIZE_QUEENS],
                    char colors[MAX_GRID_SIZE_QUEENS], int queens[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int x,
                    int y);

int inColors(char colors[MAX_GRID_SIZE_QUEENS], int size, int start, char lookFor);

int task5CrosswordGenerator(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD],
                            char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim,
                            int startSlots, int slots,
                            char words[MAX_INPUTS_CROSSWORD][MAX_WORD_LENGTH], int startWords, int numOfWords,
                            int placedWords);

void initCrossword(char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim, int dim1, int dim2);

void initSkeleton(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD], int start, int stop);

int tryPlaceWord(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD],
                 char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim,
                 int startSlots, char words[MAX_INPUTS_CROSSWORD][MAX_WORD_LENGTH], int startWords);

int checkHorizontal(char word[MAX_WORD_LENGTH], int length, int x, int y, int start,
                    char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD],
                    int crosswordDim);

int checkVertical(char word[MAX_WORD_LENGTH], int length, int startingY, int x, int y,
                  char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim);

void placeWord(char word[MAX_WORD_LENGTH], CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD], int index, int start,
               char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD]);

void removeWord(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD],
                char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim, int slot);

void restoreWords(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD],
                  char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int start, int stop);

void printGrid(char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int size);

void swap(char list[MAX_INPUTS_CROSSWORD][MAX_WORD_LENGTH], int first, int second);

int main() {
    int task = -1;
    do {
        printf("Choose an option:\n"
            "1. Robot Paths\n"
            "2. The Human Pyramid\n"
            "3. Parenthesis Validation\n"
            "4. Queens Battle\n"
            "5. Crossword Generator\n"
            "6. Exit\n");

        if (scanf("%d", &task)) {
            switch (task) {
                case 6:
                    printf("Goodbye!\n");
                    break;

                //Robot Paths
                case 1:
                    //get user input
                    int robotRow, robotColumn, robotPaths;
                    printf("Please enter the coordinates of the robot (column, row):\n");
                    scanf("%d %d", &robotColumn, &robotRow);
                // calculate num of paths and print them
                    robotPaths = task1RobotPaths(robotColumn, robotRow);
                    printf("The total number of paths the robot can take to reach home is: %d\n", robotPaths);
                    break;
                //Cheerleaders Weight calculator
                case 2:
                    float cheerleadersWeight[CHEERLEADERS_ROWS][CHEERLEADERS_COLUMNS];
                    int isNegative = 0;
                // get weights input and validate it
                    printf("Please enter the weights of the cheerleaders:\n");
                    for (int i = 0; i < CHEERLEADERS_ROWS; i++) {
                        for (int j = 0; j <= i; j++) {
                            scanf("%f", &cheerleadersWeight[i][j]);
                            if (cheerleadersWeight[i][j] < 0) {
                                isNegative = 1;
                                break;
                            }
                        }
                        if (isNegative) {
                            break;
                        }
                    }
                    if (isNegative) {
                        printf("Negative weights are not supported.\n");
                        break;
                    }
                /*calculate the weight on each cheerleader with the recursive function and print it.
                the function calculates weight on individual cheerleader and being called according
                to the num of cheerleaders */
                    printf("The total weight on each cheerleader is:\n");
                    for (int i = 0; i < CHEERLEADERS_ROWS; i++) {
                        for (int j = 0; j <= i; j++) {
                            float currentCheerleader = task2HumanPyramid(
                                cheerleadersWeight, CHEERLEADERS_ROWS, CHEERLEADERS_COLUMNS, i, j);
                            printf("%.2f ", currentCheerleader);
                        }
                        printf("\n");
                    }

                    task2HumanPyramid(cheerleadersWeight, CHEERLEADERS_ROWS, CHEERLEADERS_COLUMNS, 0, 0);
                    break;

                //Parenthesis Validation
                case 3:
                    printf("Please enter a term for validation:\n");
                /*clears buffer (either the \n that remains there or just a space between choosing task and
                 giving input. e.g 3 ({})  will work and  3\n ({}) will work*/
                    scanf("%*c");

                //gets input and keep it in buffer
                    scanf(" ");
                //determine if the expression that is in the buffer is balanced or not.
                    if (task3ParenthesisValidator(0)) {
                        printf("The parentheses are balanced correctly.\n");
                    } else {
                        printf("The parentheses are not balanced correctly.\n");
                    }
                    break;

                // The Queens Game.
                case 4:
                    int dimensionQueens;
                    char grid[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS] = {{0}};
                    int columns[MAX_GRID_SIZE_QUEENS] = {0};
                    int rows[MAX_GRID_SIZE_QUEENS] = {0};
                    char colors[MAX_GRID_SIZE_QUEENS] = {0};
                    int queens[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS] = {{0}};

                    printf("Please enter the board dimensions:\n");
                    scanf(" %d", &dimensionQueens);
                    printf("Please enter a %d*%d puzzle board:\n", dimensionQueens, dimensionQueens);
                //clears buffer before reading input, and getting the actual board input.
                    scanf("%*[^\n]");
                    for (int i = 0; i < dimensionQueens; i++) {
                        for (int j = 0; j < dimensionQueens; j++) {
                            scanf(" %c", &grid[i][j]);
                        }
                    }

                //trying to solve board
                    if (task4QueensBattle(grid, columns, rows, colors, queens, dimensionQueens, 0, 0)) {
                        printf("Solution:\n");
                        for (int i = 0; i < dimensionQueens; i++) {
                            for (int j = 0; j < dimensionQueens; j++) {
                                if (queens[i][j] == 1) {
                                    printf("X ");
                                } else {
                                    printf("* ");
                                }
                            }
                            printf("\n");
                        }
                    } else {
                        printf("This puzzle cannot be solved.\n");
                    }
                    break;

                //Crossword generator.
                case 5:
                    int dimensionCrossword, numOfSlots, numOfWords;
                    CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD];
                    char words[MAX_INPUTS_CROSSWORD][MAX_WORD_LENGTH];
                    char crosswordGrid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD];

                //get dimensions from user
                    printf("Please enter the dimensions of the crossword grid:\n");
                    scanf("%d", &dimensionCrossword);
                    initCrossword(crosswordGrid, dimensionCrossword, 0, 0);

                //get the skeleton for the crossword
                    printf("Please enter the number of slots in the crossword:\n");
                    scanf("%d", &numOfSlots);
                    initSkeleton(skeleton, 0, numOfSlots);
                    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
                    for (int i = 0; i < numOfSlots; i++) {
                        scanf("%d %d %d %c", &skeleton[i].row, &skeleton[i].column, &skeleton[i].length,
                              &skeleton[i].direction);
                    }

                //get the dictionary for the crossword
                    printf("Please enter the number of words in the dictionary:\n");
                    scanf("%d", &numOfWords);
                    while (numOfWords < numOfSlots) {
                        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n",
                               numOfSlots);
                        scanf("%d", &numOfWords);
                    }
                    printf("Please enter the words for the dictionary:\n");
                    for (int i = 0; i < numOfWords; i++) {
                        scanf("%s", words[i]);
                    }

                // checks if the crossword is solvable, if yes, prints board.
                    if (task5CrosswordGenerator(skeleton, crosswordGrid, dimensionCrossword, 0, numOfSlots, words, 0,
                                                numOfWords, 0)) {
                        printGrid(crosswordGrid, dimensionCrossword);
                    } else {
                        printf("This crossword cannot be solved.\n");
                    }
                    break;
                default:
                    printf("Please choose a task number from the list.\n");
                    break;
            }
        } else {
            scanf("%*s");
        }
    } while (task != 6);
}

//check num of paths thar the robot can reach home and returns it.
int task1RobotPaths(int column, int row) {
    int paths = 0;
    if (column == -1 || row == -1) {
        return 0;
    }
    if (column == 0 && row == 0) {
        paths += 1;
        return paths;
    }
    paths += task1RobotPaths(column - 1, row);
    paths += task1RobotPaths(column, row - 1);
    return paths;
}

//calculates and returns weight held by given cheerleader.
float task2HumanPyramid(float weights[CHEERLEADERS_ROWS][CHEERLEADERS_COLUMNS], int rows, int columns, int currentRow,
                        int currentColumn) {
    if (currentRow < 0 || currentColumn < 0 || currentRow >= rows || currentColumn >= columns
        || currentColumn > currentRow) {
        return 0;
    }

    float weightAbove1 = task2HumanPyramid(weights, rows, columns, currentRow - 1, currentColumn);
    float weightAbove2 = task2HumanPyramid(weights, rows, columns, currentRow - 1, currentColumn - 1);
    return weights[currentRow][currentColumn] + (weightAbove1 + weightAbove2) / 2;
}

//validate if the expression in the buffer is balanced or not.
int task3ParenthesisValidator(char lookFor) {
    char type;
    int isValid = 1;
    scanf("%*[^][{}()<>\n]");
    scanf("%c", &type);

    if (type == '[' || type == '{' || type == '(' || type == '<') {
        isValid = task3ParenthesisValidator(type);
    }
    if (type == ']' && lookFor == '[') {
        return 1;
    }
    if (type == '}' && lookFor == '{') {
        return 1;
    }
    if (type == ')' && lookFor == '(') {
        return 1;
    }
    if (type == '>' && lookFor == '<') {
        return 1;
    }
    if (type == ']' || type == '}' || type == ')' || type == '>') {
        isValid = 0;
        scanf("%*[^\n]%*c");
    }
    if (isValid == 0) {
        return 0;
    }
    if (type == '\n' && lookFor == 0) {
        return 1;
    }
    if (type == '\n') {
        return 0;
    }
    return task3ParenthesisValidator(lookFor);
}

//checks if the queen problem is solvable.
int task4QueensBattle(char board[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int columns[MAX_GRID_SIZE_QUEENS],
                      int rows[MAX_GRID_SIZE_QUEENS], char colors[MAX_GRID_SIZE_QUEENS],
                      int queens[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int size, int x, int y) {
    if (y == size) {
        return 1;
    }
    if (x == size) {
        return 0;
    }
    //try to place queen, if successful, try to place queen in next row.
    if (tryPlaceQueen(board, columns, rows, colors, queens, size, x, y)) {
        if (task4QueensBattle(board, columns, rows, colors, queens, size, 0, y + 1)) {
            return 1;
        }
    }
    /*if here, means the board is not solvable with queen in this square, remove queen if exists and try to solve with
     queen on the next square*/
    tryRemoveQueen(columns, rows, colors, queens, x, y);
    return task4QueensBattle(board, columns, rows, colors, queens, size, x + 1, y);
}

//try place queen on board, return 1 if successful (and place queen on board), 0 if not.
int tryPlaceQueen(char board[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int columns[MAX_GRID_SIZE_QUEENS],
                  int rows[MAX_GRID_SIZE_QUEENS], char colors[MAX_GRID_SIZE_QUEENS],
                  int queens[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int size, int x, int y) {
    if (rows[y] == 1 || columns[x] == 1 || inColors(colors, size, 0, board[y][x])) {
        return 0;
    }

    if ((queens[y + 1][x + 1] == 1) || (queens[y + 1][x - 1] == 1) ||
        (queens[y - 1][x + 1] == 1) || (queens[y - 1][x - 1] == 1)) {
        return 0;
    }
    rows[y] = 1;
    columns[x] = 1;
    colors[y] = board[y][x];
    queens[y][x] = 1;
    return 1;
}

//if queen exists, remove it from board.
void tryRemoveQueen(int columns[MAX_GRID_SIZE_QUEENS], int rows[MAX_GRID_SIZE_QUEENS],
                    char colors[MAX_GRID_SIZE_QUEENS], int queens[MAX_GRID_SIZE_QUEENS][MAX_GRID_SIZE_QUEENS], int x,
                    int y) {
    if (queens[y][x] == 1) {
        rows[y] = 0;
        columns[x] = 0;
        colors[y] = 0;
        queens[y][x] = 0;
    }
}

//check if a value is in array, in this case if a color already has a queen on it
int inColors(char colors[MAX_GRID_SIZE_QUEENS], int size, int start, char lookFor) {
    if (start == size) {
        return 0;
    }
    if (colors[start] == lookFor) {
        return 1;
    }
    return inColors(colors, size, start + 1, lookFor);
}

//checks if crossword can be made with given skeleton and dictionary.
int task5CrosswordGenerator(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD],
                            char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim,
                            int startSlots, int slots, char words[MAX_INPUTS_CROSSWORD][MAX_WORD_LENGTH],
                            int startWords, int numOfWords, int placedWords) {
    if (slots == startSlots) {
        return 1;
    }
    if (numOfWords == startWords) {
        return 0;
    }
    //try to place word in current slot, if successful, try to solve next slot, excluding all placed words
    if (tryPlaceWord(skeleton, grid, crosswordDim, startSlots, words, startWords)) {
        swap(words, startWords, placedWords);
        if (task5CrosswordGenerator(skeleton, grid, crosswordDim, startSlots + 1, slots, words, placedWords + 1,
                                    numOfWords, placedWords + 1)) {
            return 1;
        }
        /*if here, means the crossword is not solvable with placed word, revert changes, and try to place next
         word in current slot*/
        swap(words, startWords, placedWords);
        removeWord(skeleton, grid, crosswordDim, startSlots);
    }


    return task5CrosswordGenerator(skeleton, grid, crosswordDim, startSlots, slots, words, startWords + 1, numOfWords,
                                   placedWords);
}

//initialize crossword board, set all chars to '#'.
void initCrossword(char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim, int dim1, int dim2) {
    if (dim2 == crosswordDim) {
        return;
    }
    if (dim1 == crosswordDim) {
        initCrossword(grid, crosswordDim, 0, dim2 + 1);
        return;
    }
    grid[dim1][dim2] = '#';
    initCrossword(grid, crosswordDim, dim1 + 1, dim2);
}

//initialize crossword skeleton: occupied value set to 0, word value is set to "".
void initSkeleton(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD], int start, int stop) {
    if (start == stop) {
        return;
    }
    strcpy(skeleton[start].word, "");
    skeleton[start].occupied = 0;
    return initSkeleton(skeleton, start + 1, stop);
}

//try place word on board, return 1 if successful (and place word on board), 0 if not.
int tryPlaceWord(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD],
                 char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim,
                 int startSlots, char words[MAX_INPUTS_CROSSWORD][MAX_WORD_LENGTH], int startWords) {
    if ((int) strlen(words[startWords]) == skeleton[startSlots].length) {
        if (skeleton[startSlots].direction == 'H' && checkHorizontal(words[startWords], skeleton[startSlots].length,
                                                                     skeleton[startSlots].column,
                                                                     skeleton[startSlots].row, 0, grid, crosswordDim)) {
            strcpy(skeleton[startSlots].word, words[startWords]);
            skeleton[startSlots].occupied = 1;
            placeWord(words[startWords], skeleton, startSlots, 0, grid);
            return 1;
        }
        if (skeleton[startSlots].direction == 'V' && checkVertical(words[startWords], skeleton[startSlots].length,
                                                                   skeleton[startSlots].column,
                                                                   skeleton[startSlots].row, 0, grid, crosswordDim)) {
            strcpy(skeleton[startSlots].word, words[startWords]);
            skeleton[startSlots].occupied = 1;
            placeWord(words[startWords], skeleton, startSlots, 0, grid);
            return 1;
        }
    }
    return 0;
}

//check horizontally if a word can be placed (if colliding with other words).
int checkHorizontal(char word[MAX_WORD_LENGTH], int length, int x, int y, int start,
                    char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim) {
    if (start == length) {
        return 1;
    }
    if (grid[y][x + start] == '#' || grid[y][start + x] == word[start]) {
        return checkHorizontal(word, length, x, y, start + 1, grid, crosswordDim);
    }
    return 0;
}

//check vertically if a word can be placed (if colliding with other words).
int checkVertical(char word[MAX_WORD_LENGTH], int length, int x, int y, int start,
                  char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim) {
    if (start == length) {
        return 1;
    }
    if (grid[y + start][x] == '#' || grid[y + start][x] == word[start]) {
        return checkVertical(word, length, x, y, start + 1, grid, crosswordDim);
    }
    return 0;
}

//place word on board.
void placeWord(char word[MAX_WORD_LENGTH], CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD], int index, int start,
               char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD]) {
    if (start == skeleton[index].length) {
        return;
    }

    if (skeleton[index].direction == 'V') {
        grid[skeleton[index].row + start][skeleton[index].column] = word[start];
    }
    if (skeleton[index].direction == 'H') {
        grid[skeleton[index].row][skeleton[index].column + start] = word[start];
    }
    placeWord(word, skeleton, index, start + 1, grid);
}

//if word exists in given slot, remove it from board.
void removeWord(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD],
                char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int crosswordDim, int slot) {
    if (skeleton[slot].occupied) {
        strcpy(skeleton[slot].word, "");
        skeleton[slot].occupied = 0;
        initCrossword(grid, crosswordDim, 0, 0);
        restoreWords(skeleton, grid, 0, slot);
        // remove word. (wipe crossword, and put existing words)
    }
}

//re-initialize board after removing word, so no mismatches will occur.
void restoreWords(CrosswordSkeleton skeleton[MAX_INPUTS_CROSSWORD],
                  char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int start, int stop) {
    if (start == stop) {
        return;
    }
    placeWord(skeleton[start].word, skeleton, start, 0, grid);
    restoreWords(skeleton, grid, start + 1, stop);
}

//prints grid (allowed to use loops for this task).
void printGrid(char grid[MAX_GRID_SIZE_CROSSWORD][MAX_GRID_SIZE_CROSSWORD], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("| %c ", grid[i][j]);
        }
        printf("|\n");
    }
}

//with given list and 2 positions, swap the elements in the list.
void swap(char list[MAX_INPUTS_CROSSWORD][MAX_WORD_LENGTH], int first, int second) {
    char temp[MAX_WORD_LENGTH];
    strcpy(temp, list[first]);
    strcpy(list[first], list[second]);
    strcpy(list[second], temp);
}
