#include "bishop.h"
#include <iostream>
#include <string>
using namespace std;
// this is a test harness for testing all the features of king.
int main(){
    ChessSquare initialPosition(3, 3);
    King White_K(ChessColour::White, initialPosition);
    int choice;
    while (true){
        cout << "select a test to do:" << endl;
        cout << "1. Valid Movement Test" << endl;
        cout << "2. Invalid Movement Test" << endl;
        cout << "3. Path Generation Test" << endl;
        cout << "4. Board Boundary Test" << endl;
        cout << "5. No Movement Test" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        ChessSquare destination(0, 0);
        int row, col;
        switch(choice){
            case 1:  // valid move test;
                cin << row << col;
                destination.setCoords(row, col);
                if (White_K.isValidMove(destination)){
                    cout << "ValidMove Test passed!!" << endl;
                }
                else{
                    cout << "ValidMove Test NOT passed!!" << endl;
                }
                break;
            case 2: // invalid move test
                cin << row << col;
                destination.setCoords(row, col);
                if (!White_K.isValidMove(destination)){
                    cout << "InvalidMove test passed!!" << endl;
                }
                else{
                    cout << "InvalidMove test not passed!!" << endl;
                }
                break;
            case 3: //path generation test
                cin << row << col;
                destination.setCoords(row, col);
                if (White_K.isValidMove(destination)){
                    vector<ChessSquare> result = White_K.generatePath(destination);
                    cout << "The path is :" << endl;
                    for (const auto &p : path){
                        cout << "Row is :" << p.getRow();
                        cout << " Column is :" << p.getColumn() << endl;
                    }
                }
                else{
                    cout << "Input destination is not valid!" << endl;
                }
                break;
            case 4: // Board Boundary Test
                cout << "Testing board boundary by moving to your next input:" << endl;
                cout << "input two integers that are row and column which is out of bound: (can be 8 8 or 10 10)" << endl;
                cin << row << col;
                destination.setCoords(row, col);
                if (!White_K.isValidMove(destination)) {
                    cout << "BoardBoundary test passed!!" << endl;
                } else {
                    cout << "BoardBoundary test NOT passed!!" << endl;
                }
                break;

            case 5: // No Movement Test
                cout << "Testing no movement by staying at (3, 3)" << endl;
                if (!White_K.isValidMove(initialPosition)) {
                    cout << "NoMovement test passed!!" << endl;
                } else {
                    cout << "NoMovement test NOT passed!!" << endl;
                }
                break;
                

        }
    }
}

