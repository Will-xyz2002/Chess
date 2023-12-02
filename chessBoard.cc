#include "chessBoard.h"
#include <sstream>
#include <iostream>

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
    whiteKing = other.whiteKing;
    blackKing = other.blackKing;
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
    board[0][7] = Rook {ChessColour::Black, {0, 7}};

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
    board[7][7] = Rook {ChessColour::White, {7, 7}};

    blackKing = &board[0][4];
    whiteKing = &board[7][4];

    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            notifyObservers(board[r][c]);
        }
    }
}                                                   


void ChessBoard::addPiece(char pieceType, std::string position) {
    ChessSquare location = convertPosition(position); // convert user input to chessSquare
    int r = location.getRow();
    int c = location.getColumn(); 

    // add piece accordingly
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

void ChessBoard::addPiece(ChessPiece &piece) {
    int r = piece.getCoords().getRow();
    int c = piece.getCoords().getColumn();
    if (piece.getType() == ChessType::Pawn) board[r][c] = Pawn{piece.getColour(), {r, c}};
    else if (piece.getType() == ChessType::Rook) board[r][c] = Rook{piece.getColour(), {r, c}};
    else if (piece.getType() == ChessType::Knight) board[r][c] = Knight{piece.getColour(), {r, c}};
    else if (piece.getType() == ChessType::Bishop) board[r][c] = Bishop{piece.getColour(), {r, c}};
    else if (piece.getType() == ChessType::Queen) board[r][c] = Queen{piece.getColour(), {r, c}};
    else if (piece.getType() == ChessType::King) board[r][c] = King{piece.getColour(), {r, c}};
    else if (piece.getType() == ChessType::Empty) board[r][c] = Empty{{r, c}};
}


void ChessBoard::removePiece(std::string position) {
    ChessSquare location = convertPosition(position);
    int r = location.getRow();
    int c = location.getColumn();
    if (!board[r][c].isEmpty()) { // removePiece only occur when the piece is not empty
        board[r][c] = Empty {{r, c}};
        notifyObservers(board[r][c]);
    }
}


bool ChessBoard::kingIsUnderAttack(ChessColour colour) {
    // get what piece colour is attacking the king, and the king's location
    ChessColour opponent = (colour == ChessColour::White) ? ChessColour::Black : ChessColour::White;
    ChessSquare king = (colour == ChessColour::White) ? whiteKing->getCoords() : blackKing->getCoords();

    // evaluate every opponent piece, whether they can attack the player's king
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            ChessSquare opponent_square{r, c};
            if (board[r][c].getColour() == opponent && isUnderAttack(king, opponent_square)) return true;
        }
    }
    return false;
}                 
    

bool ChessBoard::isValidMove(ChessSquare &initial, ChessSquare &dest, ChessColour turn) {
    // get the chessPiece that correspond to initial and destination chessSquare
    ChessPiece source = board[initial.getRow()][initial.getColumn()];
    ChessPiece destination = board[dest.getRow()][dest.getColumn()];

    // if the player move a piece that is different from their color, it is invalid
    if (source.getColour() != turn) return false;

    // if the initial piece and the final piece have the same color, it is invalid
    if (source.getColour() == destination.getColour()) return false;

    // otherwise, evaluate valid move based on the type of initial
    bool validMove;
    if (source.getType() == ChessType::Empty) {
        validMove = false;
    }
    else if (source.getType() == ChessType::Rook) {
        Rook r {source.getColour(), source.getCoords()};
        if (source.hasMoved()) r.setMoved(true);
        validMove = r.isValidMove(destination);
    }
    else if (source.getType() == ChessType::Pawn) {
        Pawn p {source.getColour(), source.getCoords()};
        if (source.hasMoved()) p.setMoved(true);
        validMove = p.isValidMove(destination);
    }
    else if (source.getType() == ChessType::Bishop) {
        Bishop b {source.getColour(), source.getCoords()};
        if (source.hasMoved()) b.setMoved(true);
        validMove = b.isValidMove(destination);
    }
    else if (source.getType() == ChessType::Knight) {
        Knight n {source.getColour(), source.getCoords()};
        if (source.hasMoved()) n.setMoved(true);
        validMove = n.isValidMove(destination);
    }
    else if (source.getType() == ChessType::Queen) {
        Queen q {source.getColour(), source.getCoords()};
        if (source.hasMoved()) q.setMoved(true);
        validMove = q.isValidMove(destination);
    }
    else if (source.getType() == ChessType::King) {
        King k {source.getColour(), source.getCoords()};
        if (source.hasMoved()) k.setMoved(true);
        validMove = k.isValidMove(destination);
    }

    if (validMove) return true; // move is valid

    // exceptions: castling and en passant
    if (source.getType() == ChessType::King) return isCastlingPossible(initial, dest);
    if (source.getType() == ChessType::Pawn) return isEnPassantPossible(initial, dest);
    return false;
}       


bool ChessBoard::isValidPath(ChessSquare &initial, ChessSquare &dest) {
    // get chesspieces that correspond to the source and destination that the piece want to move to
    ChessPiece source = board[initial.getRow()][initial.getColumn()];
    ChessPiece destination = board[dest.getRow()][dest.getColumn()];
    std::vector<ChessSquare> path;

    // generate path based on the type of initial
    if (source.getType() == ChessType::Empty) {
        Empty e {source.getCoords()};
        path = e.generatePath(destination);
    }
    else if (source.getType() == ChessType::Rook) {
        Rook r {source.getColour(), source.getCoords()};
        path = r.generatePath(destination);
    }
    else if (source.getType() == ChessType::Pawn) {
        Pawn p {source.getColour(), source.getCoords()};
        path = p.generatePath(destination);
    }
    else if (source.getType() == ChessType::Bishop) {
        Bishop b {source.getColour(), source.getCoords()};
        path = b.generatePath(destination);
    }
    else if (source.getType() == ChessType::Knight) {
        Knight n {source.getColour(), source.getCoords()};
        path = n.generatePath(destination);
    }
    else if (source.getType() == ChessType::Queen) {
        Queen q {source.getColour(), source.getCoords()};
        path = q.generatePath(destination);
    }
    else if (source.getType() == ChessType::King) {
        King k {source.getColour(), source.getCoords()};
        path = k.generatePath(destination);
    }

    // if there is no path, or the path that the piece will take has no obstacle between it, return true
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

    // initiate the move
    board[finalRow][finalCol] = board[currentRow][currentCol];
    board[finalRow][finalCol].setCoords(finalRow, finalCol);
    board[finalRow][finalCol].setMoved(true);

    // if the moving piece is the king, update the king's pointer location
    if (board[finalRow][finalCol].getType() == ChessType::King) {
        if (board[finalRow][finalCol].getColour() == ChessColour::White) whiteKing = &board[finalRow][finalCol];
        else blackKing = &board[finalRow][finalCol];
    }

    // the initial square become empty after move
    board[currentRow][currentCol] = Empty {{currentRow, currentCol}};
} 

bool ChessBoard::isValidBoard() {
    // if there are any pawns at the first or last row after setup, return false
    for (int c = 0; c < BOARD_DIMENSION; ++c) {
        if (board[0][c].getType() == ChessType::Pawn) return false;
        if (board[7][c].getType() == ChessType::Pawn) return false;
    }

    // evaluate whether there is exactly one white king and one black king. If not, return false
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
                    blackKingCount += 1;
                    blackKingPos.setCoords(r, c);
                }
            }
        }
    }
    if (whiteKingCount != 1 || blackKingCount != 1) return false;
    whiteKing = &board[whiteKingPos.getRow()][whiteKingPos.getColumn()];
    blackKing = &board[blackKingPos.getRow()][blackKingPos.getColumn()];

    // evaluate whether any king is in check. If true, return false
    if (kingIsUnderAttack(ChessColour::White) || kingIsUnderAttack(ChessColour::Black)) {
        whiteKing = nullptr;
        blackKing = nullptr;
        return false;
    }
    return true; // the board is valid
}

void ChessBoard::emptyBoard() {
    // emptying the board and initialize the board again
    board.clear();
    whiteKing = nullptr;
    blackKing = nullptr;
    std::vector<ChessPiece> row;
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            row.emplace_back(Empty{{r, c}});
            notifyObservers(board[r][c]);
        }
        board.emplace_back(row);
        row.clear();
    }
}

void ChessBoard::attach(Observer *o) {
    observers.emplace_back(o);
}


void ChessBoard::notifyObservers(ChessPiece &piece) {
    int length = observers.size();
    for (int i = 0; i < length; ++i) {
        observers[i]->notify(piece);
    }
}

// for set up only
std::ostream &operator<<(ostream &out, ChessBoard &b) {
    int column = 8;
    char row = 'a';
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        out << column << ' ';
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            out << b.board[r][c].getDisplay();
        }
        out << endl;
        column -= 1;
    }
    out << endl;
    out << ' ' << ' ';
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        out << row;
        row += 1;
    }
    out << endl;
    return out;
}



// -------------------------------
// PRIVATE METHODS
// -------------------------------
bool ChessBoard::isUnderAttack(ChessSquare &target, ChessSquare &piece) {
    // return whether it is possible for the piece to attack the target
    ChessColour colour = board[piece.getRow()][piece.getColumn()].getColour();
    return isValidMove(piece, target, colour) && isValidPath(piece, target); 
}


bool ChessBoard::validMoveExist(ChessColour colour) {
    // find all pieces that correspond to the colour of the player
    std::vector<ChessPiece> allPieces;
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            if (board[r][c].getColour() == colour) allPieces.emplace_back(board[r][c]);
        }
    }

    // if at least one piece has a validMove (valid movement by rule, no obstacle, king is not in check), return true
    int length = allPieces.size();
    for (int i = 0; i < length; i++) {
        if (validMoveExist(allPieces[i].getCoords())) return true;
    }
    return false;
}

bool ChessBoard::validMoveExist(ChessSquare piece) {
    // evaluate whether the piece at the particular chessSquare can make a valid move
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            ChessSquare square {r, c};
            if (isValidMove(piece, square, board[piece.getRow()][piece.getColumn()].getColour()) && 
                isValidPath(piece, square)) {
                    ChessBoard temp = *this;
                    temp.chessMove(piece, square);
                    if (!temp.kingIsUnderAttack(board[piece.getRow()][piece.getColumn()].getColour())) return true;
                    
            }
        }
    }
    return false;
}

void ChessBoard::pawnPromotion(int row, int column, ChessColour colour) {
    char pieceType;
    do {
        cin >> pieceType;
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
    } while (true);
}


bool ChessBoard::isCastlingPossible(ChessSquare &initial, ChessSquare &dest) {
    return false;
}

bool ChessBoard::isEnPassantPossible(ChessSquare &initial, ChessSquare &dest) {
    return false;
}
