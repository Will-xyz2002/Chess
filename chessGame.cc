#include "chessGame.h"
#include "chessPiece.h"

ChessGame::ChessGame(ChessBoard board, bool whiteTurn, Player p1, Player p2): 
                    board{board}, whiteTurn{whiteTurn}, p1{p1}, p2{p2} {
    
    cout << board.getTextDisplay();
    if (whiteTurn) cout << "White turn." << endl;
    else cout << "Black turn." << endl;
}

bool ChessGame::isWhiteTurn() { return whiteTurn; }
bool ChessGame::gameWon() { return isWon; }

// -- INPUT CHECK ----
bool checkValidColumn(std::string position) {
    return (position[0] < 'a' || position[0] > 'h');
}

bool checkValidRow(std::string position) {
    return (position[1] < '1' || position[1] > '8');
}
// ----------------


void ChessGame::makeAMove(std::string initial, std::string dest) {
    // first check input
    if (initial.length() != 2 || dest.length() != 2) cout << "Invalid input. Please try again." << endl;
    else if (!checkValidColumn(initial) || !checkValidColumn(dest)) cout << "Invalid column - needs to be [a-h]" << endl;
    else if (!checkValidRow(initial) || !checkValidRow(dest)) cout << "Invalid row - needs to be [1-8]" << endl;
    else {
        ChessColour colour = whiteTurn ? ChessColour::White : ChessColour::Black;
        ChessSquare source = convertPosition(initial);
        ChessSquare destination = convertPosition(dest);
        ChessPiece initialPiece = board.getPiece(source.getRow(), source.getColumn());
        ChessPiece targetPiece = board.getPiece(destination.getRow(), destination.getColumn());

        // check valid move and path
        if (!board.isValidMove(initialPiece, targetPiece, colour) || !board.isValidPath(initialPiece, targetPiece)) return;

        // check whether the move would put the player's own king in check
        ChessBoard temp = board;
        temp.chessMove(initialPiece.getCoords(), targetPiece.getCoords());
        if (temp.kingIsUnderAttack(colour)) {
            cout << "Invalid move (king is in check after move). Please try again." << endl;
        }

        // if successful, log the move to the moveLog, and initiate the chess move
        ChessMove move {initialPiece, targetPiece};
        moveLog.emplace_back(move);
        board.chessMove(initialPiece.getCoords(), targetPiece.getCoords());
        cout << board.getTextDisplay();

        // switch turn
        whiteTurn = whiteTurn ? false : true;

        // check for checkmate/stalemate
        colour = whiteTurn ? ChessColour::White : ChessColour::Black;
        bool isChecked = board.kingIsUnderAttack(colour);
        if (!board.validMoveExist(colour)) {
            if (isChecked) {
                isWon = true;
                isWhiteWin = whiteTurn ? false : true;
                if (isWhiteWin) cout << "Checkmate! White wins!" << endl;
                else cout << "Checkmate! Black wins!" << endl;
                return;

            } else {
                isWon = true;
                isStalemate = true;
                cout << "Stalemate!" << endl;
                return;
            }
        } else if (isChecked) {
            if (whiteTurn) cout << "White is in check." << endl;
            else cout << "Black is in check." << endl;
        }

        if (whiteTurn) cout << "White move." << endl;
        else cout << "Black move." << endl;
    }
}



void ChessGame::makeAMove() {
    if (whiteTurn) p1.makeAMove();
    else p2.makeAMove();
    cout << board.getTextDisplay();
    whiteTurn = whiteTurn ? false : true;

    ChessColour colour = whiteTurn ? ChessColour::White : ChessColour::Black;
    bool isChecked = board.kingIsUnderAttack(colour);
    if (!board.validMoveExist(colour)) {
        if (isChecked) {
            isWon = true;
            isWhiteWin = whiteTurn ? false : true;
            if (isWhiteWin) cout << "Checkmate! White wins!" << endl;
            else cout << "Checkmate! Black wins!" << endl;
            return;   
        } else {
            isWon = true;
            isStalemate = true;
            cout << "Stalemate!" << endl;
            return;
        }
    } else if (isChecked) {
        if (whiteTurn) cout << "White is in check." << endl;
        else cout << "Black is in check." << endl;
    }
    if (whiteTurn) cout << "White move." << endl;
    else cout << "Black move." << endl;
}



void ChessGame::undo() {
    ChessMove move = moveLog[moveLog.size()-1];
    moveLog.pop_back();
    ChessPiece piece1 = move.getInitial();
    ChessPiece piece2 = move.getDest();
    board.addPiece(piece1);
    board.addPiece(piece2);
    cout << board.getTextDisplay();
    whiteTurn = whiteTurn ? false : true;
}


void ChessGame::resign() {
    isWon = true;
    isWhiteWin = whiteTurn ? false : true;
}


