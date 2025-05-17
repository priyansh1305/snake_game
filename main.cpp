#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
// height and width of the boundary
const int width = 80;
const int height = 20;

//Snake head coordinates of snake (x,y)
int x, y;
//food coordinates
int fruitcoordX, fruitcoordY;
//value of the score
int playerscore;
//array to store the coordinates of snake tail (x axis y axis)
int snakeTailX[100], snakeTailY[100];
// variable to the length of the tail
int snakeTailLen;

//for storing snake's moving snakesDirection
enum snakesdirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

//snakeDirection variable
snakesdirection sDir;
//boolean variable for checking if the game is over or not
bool isGameOver;

void GameInit() {
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitcoordX = rand() % width;
    fruitcoordY = rand() % height;
    playerscore = 0;
    // snakeTailLen=0;
}

// Function For creating the game board and rendering
void GameRender(string playerName) {
    system("cls");
    //creating top walls with a dash(-)
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;


    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            //creating the walls with "/"
            if (j == 0 || j == width)
                cout << "|";
            //creating the head of the snake with '0'
            if (i == y && j == x)

                cout << "0";
                // creating the snake food with #
            else if (i == fruitcoordY && j == fruitcoordX)
                cout << "#";
            //creating snake body with o
            else {
                bool prtail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        cout << "o";
                        prtail = true;
                    }
                }
                if (!prtail)
                    cout << " ";
            }
        }
        cout << endl;
    }
    //creating bottom walls with "-"
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;
    //display player score
    cout << playerName << "'s score: " << playerscore << endl;
}

//Function to update the game state
void UpdateGame() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (sDir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    //check for snake's collison with wall (|)
    if (x >= width || y >= height || x < 0 || y < 0)
        isGameOver = true;

    //check for collision with the tail (o)
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            isGameOver = true;
    }
    //check for snakes collision with food (#)
    if (x == fruitcoordX && y == fruitcoordY) {
        playerscore += 10;
        fruitcoordX = rand() % width;
        fruitcoordY = rand() % height;
        snakeTailLen++;
    }
}

// funtion to set the game difficulty level
int SetDifficulty() {
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
            "\nNOTE: if not chosen or pressed any other "
            "key, the difficulty will be automatically set "
            "to medium\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
        case 1:
            dfc = 500;
            break;
        case 2:
            dfc = 400;
            break;
        case 3:
            dfc = 300;
            break;
        case 4:
            dfc = 200;
            break;
    }
    return dfc;
}

//Funtion to handle user UserInput
void UserInput() {
    //checks if a key is pressed or not
    if (_kbhit()) {
        //getting the key pressed
        switch (_getch()) {
            case 'a':
                sDir = LEFT;
                break;
            case 'd':
                sDir = RIGHT;
                break;
            case 'w':
                sDir = UP;
                break;
            case 's':
                sDir = DOWN;
                break;
            case 'x':
                isGameOver = true;
                break;
        }
    }
}

// main function / game looping function
int main() {
    string playerName;
    cout << "Enter Your Name: ";
    cin >> playerName;
    int dfc = SetDifficulty();
    GameInit();
    while (!isGameOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        Sleep(dfc);
    }
    return 0;
}
