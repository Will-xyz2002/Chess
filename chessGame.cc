#include "chessGame.h"
#include "chessPiece.h"

// -- INPUT CHECK ----
bool checkValidColumn(std::string position) {
    return !(position[0] < 'a' || position[0] > 'h');
}

bool checkValidRow(std::string position) {
    return !(position[1] < '1' || position[1] > '8');
}
// ----------------

ChessGame::ChessGame(ChessBoard board, bool whiteTurn, Player p1, Player p2): 
                    board{board}, whiteTurn{whiteTurn}, p1{p1}, p2{p2} {
                        
    textDisplay = new TextDisplay();
    textDisplay->setBoard(board);
    board.attach(textDisplay);
    cout << *textDisplay;
    textDisplay->outputTurn(whiteTurn);
}

ChessGame::~ChessGame() {
    delete textDisplay;
}

bool ChessGame::isWhiteTurn() { return whiteTurn; }
bool ChessGame::gameWon() { return isWon; }


void ChessGame::makeAMove(std::string initial, std::string dest) {
    // Checking input - valid location on the chessBoard
    if (initial.length() != 2 || dest.length() != 2) {
        textDisplay->outputInvalidPiece();
        return;
    }
    if (!checkValidColumn(initial) || !checkValidColumn(dest)) {
        textDisplay->outputInvalidColumn();
        return;
    }
    if (!checkValidRow(initial) || !checkValidRow(dest)) {
        textDisplay->outputInvalidRow();
        return;
    }

    // Checking whether such move is legal
    ChessColour colour = whiteTurn ? ChessColour::White : ChessColour::Black;
    ChessSquare source = convertPosition(initial);
    ChessSquare destination = convertPosition(dest);

    bool validMove;
    bool validPath;

   
    if (!board.isValidMove(source, destination, colour) || !board.isValidPath(source, destination)) {
        textDisplay->outputInvalidMove();
        return;
    }

    ChessBoard temp = board;
    temp.chessMove(source, destination);
    if (temp.kingIsUnderAttack(colour)) {
        textDisplay->outputInvalidMove();
        return;
    }

    // if approved, add move to moveLog and make a chess move
    ChessPiece initialPiece = board.getPiece(source.getRow(), source.getColumn());
    ChessPiece targetPiece = board.getPiece(destination.getRow(), destination.getColumn());
    ChessMove move {initialPiece, targetPiece};
    moveLog.emplace_back(move);
    board.chessMove(initialPiece.getCoords(), targetPiece.getCoords());

    initialPiece = board.getPiece(source.getRow(), source.getColumn());
    targetPiece = board.getPiece(destination.getRow(), destination.getColumn());
    textDisplay->notify(initialPiece);
    textDisplay->notify(targetPiece);

    cout << *textDisplay;
    whiteTurn = whiteTurn ? false : true;


    // evaluate checkmate/check/stalemate
    colour = whiteTurn ? ChessColour::White : ChessColour::Black;
    bool isChecked = board.kingIsUnderAttack(colour);

    if (!board.validMoveExist(colour)) {
        if (isChecked) {
            isWon = true;
            isWhiteWin = !whiteTurn;
            textDisplay->outputCheckmate(whiteTurn);
            return;
        }
        else {
            isWon = true;
            isStalemate = true;
            textDisplay->outputStalemate();
            return;
        }
    }
    if (isChecked) {
        textDisplay->outputCheck(whiteTurn);
    }
    // output turn
    textDisplay->outputTurn(whiteTurn);
}



void ChessGame::makeAMove() {
    if (whiteTurn) p1.makeAMove();
    else p2.makeAMove();
    cout << textDisplay;
    whiteTurn = whiteTurn ? false : true;
    ChessColour colour = whiteTurn ? ChessColour::White : ChessColour::Black;
    bool isChecked = board.kingIsUnderAttack(colour);
    if (!board.validMoveExist(colour)) {
        if (isChecked) {
            isWon = true;
            isWhiteWin = !whiteTurn;
            textDisplay->outputCheckmate(whiteTurn);
            return;
        }
        else {
            isWon = true;
            isStalemate = true;
            textDisplay->outputStalemate();
            return;
        }
    }
    if (isChecked) {
        textDisplay->outputCheck(whiteTurn);
    }
    textDisplay->outputTurn(whiteTurn);
}



void ChessGame::undo() {
    ChessMove move = moveLog[moveLog.size()-1];
    moveLog.pop_back();
    ChessPiece piece1 = move.getInitial();
    ChessPiece piece2 = move.getDest();
    board.addPiece(piece1);
    board.addPiece(piece2);
    board.notifyObservers(piece1);
    board.notifyObservers(piece2);
    cout << *textDisplay;
    whiteTurn = whiteTurn ? false : true;
}


void ChessGame::resign() {
    isWon = true;
    isWhiteWin = !whiteTurn;
    textDisplay->outputResign(whiteTurn);
}


