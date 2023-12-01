#include "chessBoard.h"
#include <sstream>

// convertPosition(position) convert string representation of the chess location
// (eg. e4) to chessSquare coordinate (eg. {7, 4})
ChessSquare convertPosition(string position) {
    istringstream socks(position);
    int square_row, square_column;
    int row;
    char column;
    socks >> column;
    socks >> row;
    square_column = column - 'a';
    square_row = BOARD_DIMENSION - row;
    return {square_row, square_column};
}

// CONSTRUCTOR
ChessBoard::ChessBoard() {
    std::vector<ChessPiece> row;
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            row.emplace_back(Empty{{r, c}});
        }
        board.emplace_back(row);
        row.clear();
    }
}

// COPY CONSTRUCTOR
ChessBoard::ChessBoard(const ChessBoard &other) {
    board = other.board;
    observers = other.observers;
    whiteKing = make_unique<King>(other.whiteKing);
    blackKing = make_unique<King>(other.blackKing);
}
    
ChessPiece ChessBoard::getPiece(int row, int column) { return board[row][column]; }

// initialize the board
void ChessBoard::init() {
    // first row
    board[0][0] = Rook   {ChessColour::Black, {0, 0}};
    board[0][1] = Knight {ChessColour::Black, {0, 1}};
    board[0][2] = Bishop {ChessColour::Black, {0, 2}};
    board[0][3] = Queen  {ChessColour::Black, {0, 3}};
    board[0][4] = King   {ChessColour::Black, {0, 4}};
    board[0][5] = Bishop {ChessColour::Black, {0, 5}};
    board[0][6] = Knight {ChessColour::Black, {0, 6}};
    board[0][7] = Knight {ChessColour::Black, {0, 7}};

    // second to seventh row
    for (int c = 0; c < BOARD_DIMENSION; ++c) {
        board[1][c] = Pawn {ChessColour::Black, {1, c}};
        board[2][c] = Empty {{2, c}};
        board[3][c] = Empty {{3, c}};
        board[4][c] = Empty {{4, c}};
        board[5][c] = Empty {{5, c}};
        board[6][c] = Pawn {ChessColour::White, {6, c}};
    }

    // eighth row
    board[7][0] = Rook   {ChessColour::White, {7, 0}};
    board[7][1] = Knight {ChessColour::White, {7, 1}};
    board[7][2] = Bishop {ChessColour::White, {7, 2}};
    board[7][3] = Queen  {ChessColour::White, {7, 3}};
    board[7][4] = King   {ChessColour::White, {7, 4}};
    board[7][5] = Bishop {ChessColour::White, {7, 5}};
    board[7][6] = Knight {ChessColour::White, {7, 6}};
    board[7][7] = Knight {ChessColour::White, {7, 7}};

    if (blackKing != nullptr) blackKing.reset();
    if (whiteKing != nullptr) whiteKing.reset();

    blackKing = make_unique<King>(board[0][4]);
    whiteKing = make_unique<King>(board[7][4]);

    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            notifyObservers(board[r][c]);
        }
    }
}                                                   


void ChessBoard::addPiece(char pieceType, std::string position) {
    ChessSquare location = convertPosition(position);
    int r = location.getRow();
    int c = location.getColumn(); 
    if (pieceType == 'r') board[r][c] = Rook{ChessColour::Black, location};
    else if (pieceType == 'R') board[r][c] = Rook{ChessColour::White, location};
    else if (pieceType == 'n') board[r][c] = Knight{ChessColour::Black, location};
    else if (pieceType == 'N') board[r][c] = Knight{ChessColour::White, location};
    else if (pieceType == 'b') board[r][c] = Bishop{ChessColour::Black, location};
    else if (pieceType == 'B') board[r][c] = Bishop{ChessColour::White, location};
    else if (pieceType == 'q') board[r][c] = Queen{ChessColour::Black, location};
    else if (pieceType == 'Q') board[r][c] = Queen{ChessColour::White, location};
    else if (pieceType == 'p') board[r][c] = Pawn{ChessColour::Black, location};
    else if (pieceType == 'P') board[r][c] = Pawn{ChessColour::White, location};
    else if (pieceType == 'k') board[r][c] = King{ChessColour::Black, location};
    else if (pieceType == 'K') board[r][c] = King{ChessColour::White, location};
    notifyObservers(board[r][c]);
}

void ChessBoard::removePiece(std::string position) {
    ChessSquare location = convertPosition(position);
    int r = location.getRow();
    int c = location.getColumn();
    if (!board[r][c].isEmpty()) {
        board[r][c] = Empty {{r, c}};
        notifyObservers(board[r][c]);
    }
}


bool ChessBoard::kingIsUnderAttack(ChessColour colour) {
    ChessColour opponent = (colour == ChessColour::White) ? ChessColour::Black : ChessColour::White;
    if (colour == ChessColour::White) {
        for (int r = 0; r < BOARD_DIMENSION; ++r) {
            for (int c = 0; c < BOARD_DIMENSION; ++c) {
                if (board[r][c].getColour() == opponent && isUnderAttack(*whiteKing, board[r][c])) return true;
            }
        }
    } else if (colour == ChessColour::Black) {
        for (int r = 0; r < BOARD_DIMENSION; ++r) {
            for (int c = 0; c < BOARD_DIMENSION; ++c) {
                if (board[r][c].getColour() == opponent && isUnderAttack(*blackKing, board[r][c])) return true;
            }
        }
    }
    return false;
}                 
    

bool ChessBoard::isValidMove(ChessPiece &initial, ChessPiece &dest, ChessColour turn) {
    if (initial.getColour() != turn) return false;
    if (initial.getColour() == dest.getColour()) return false;
    if (initial.isValidMove(dest)) return true;
    // edge cases: en passant, castling

    if (initial.getType() == ChessType::King) return isCastlingPossible(initial, dest);
    if (initial.getType() == ChessType::Pawn) return isEnPassantPossible(initial, dest);
    return false;
}       


bool ChessBoard::isValidPath(ChessPiece &initial, ChessPiece &dest) {
    std::vector<ChessSquare> path = initial.generatePath(dest);
    int length = path.size();
    if (length == 0) return true;
    int r, c;
    for (int i = 0; i < length; i++) {
        r = path[i].getRow();
        c = path[i].getColumn();
        if (!board[r][c].isEmpty()) return false;
    }
    return true;
}      


void ChessBoard::chessMove(ChessSquare initial, ChessSquare dest) {
    int currentRow = initial.getRow();
    int currentCol = initial.getColumn();
    int finalRow = dest.getRow();
    int finalCol = dest.getColumn();
    board[finalRow][finalCol] = board[currentRow][currentCol];
    board[finalRow][finalCol].setCoords(finalRow, finalCol);
    if (board[finalRow][finalCol].getType() == ChessType::King) {
        if (board[finalRow][finalCol].getColour() == ChessColour::White) whiteKing->setCoords(finalRow, finalCol);
        else blackKing->setCoords(finalRow, finalCol);
    }
    board[currentRow][currentCol] = Empty {{currentRow, currentCol}};

    // special case: promotion
    if (finalRow == 0 && board[finalRow][finalCol].getColour() == ChessColour::White &&
        board[finalRow][finalCol].getType() == ChessType::Pawn) {
        pawnPromotion(finalRow, finalCol, ChessColour::White);

    } else if (finalRow == 7 && board[finalRow][finalCol].getColour() == ChessColour::Black &&
        board[finalRow][finalCol].getType() == ChessType::Pawn) {
        pawnPromotion(finalRow, finalCol, ChessColour::Black);
    }

    notifyObservers(board[currentRow][currentCol]);
    notifyObservers(board[finalRow][finalCol]);
} 

bool ChessBoard::isValidBoard() {
    for (int c = 0; c < BOARD_DIMENSION; ++c) {
        if (board[0][c].getType() == ChessType::Pawn) return false;
        if (board[7][c].getType() == ChessType::Pawn) return false;
    }
    ChessSquare whiteKingPos {0, 0};
    ChessSquare blackKingPos {0, 0};
    int whiteKingCount = 0;
    int blackKingCount = 0;
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            if (board[r][c].getType() == ChessType::King) {
                if (board[r][c].getColour() == ChessColour::White) {
                    whiteKingCount += 1;
                    whiteKingPos.setCoords(r, c);
                }
                else {
                    blackKingCount +=1;
                    blackKingPos.setCoords(r, c);
                }
            }
        }
    }
    if (whiteKingCount != 1 || blackKingCount != 1) return false;
    if (whiteKing != nullptr) whiteKing.reset();
    if (blackKing != nullptr) blackKing.reset();
    whiteKing = make_unique<King>(ChessColour::White, whiteKingPos);
    blackKing = make_unique<King>(ChessColour::Black, blackKingPos);
    if (kingIsUnderAttack(ChessColour::White) || kingIsUnderAttack(ChessColour::Black)) return false;
    return true;
}

void ChessBoard::emptyBoard() {
    board.clear();
    whiteKing.reset();
    blackKing.reset();
    whiteKing = nullptr;
    blackKing = nullptr;
    std::vector<ChessPiece> row;
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            row.emplace_back(Empty{{r, c}});
        }
        board.emplace_back(row);
        row.clear();
    }
}

void ChessBoard::attach(Observer &o) {
    observers.emplace_back(o);
}

void ChessBoard::notifyObservers(ChessPiece &piece) {
    int length = observers.size();
    for (int i = 0; i < length; ++i) {
        observers[i]->notify(piece);
    }
}



// PRIVATE METHODS
bool ChessBoard::isUnderAttack(ChessPiece &target, ChessPiece &piece) {
    return isValidMove(piece, target, piece.getColour()) &&
           isValidPath(piece, target);
}


bool ChessBoard::validMoveExist(ChessColour colour) {
    std::vector<ChessPiece> allPieces;
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            if (board[r][c].getColour() == colour) allPieces.emplace_back(board[r][c]);
        }
    }
    int length = allPieces.size();
    for (int i = 0; i < length; i++) {
        if (validMoveExist(allPieces[i])) return true;
    }
    return false;
}

bool ChessBoard::validMoveExist(ChessPiece &piece) {
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            if (isValidMove(piece, board[r][c], piece.getColour()) && isValidPath(piece, board[r][c])) return true;
        }
    }
    return false;
}

void ChessBoard::pawnPromotion(int row, int column, ChessColour colour) {
    char pieceType;
    while (cin >> pieceType) {
        pieceType = toupper(pieceType);
        if (pieceType == 'Q') {
            board[row][column] = Queen{colour, {row, column}};
            break;
        }
        else if (pieceType == 'R') {
            board[row][column] = Rook{colour, {row, column}};
            break;
        }
        else if (pieceType == 'B') {
            board[row][column] = Bishop{colour, {row, column}};
            break;
        }
        else if (pieceType == 'N') {
            board[row][column] = Knight{colour, {row, column}};
            break;
        }
        else {
            cout << "Invalid promotion piece. Please enter again." << endl;
        }
    }
}


bool ChessBoard::isCastlingPossible(ChessPiece &initial, ChessPiece &dest) {

}

bool ChessBoard::isEnPassantPossible(ChessPiece &initial, ChessPiece &dest) {

}
