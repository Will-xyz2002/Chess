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


// pawnMoveTwoForward(move) return whether the given move is a pawn moving two square forward
bool pawnMoveTwoForward(ChessMove &move) {
    ChessPiece initial = move.getInitial();
    ChessPiece dest = move.getDest();
    if (initial.getType() != ChessType::Pawn) return false;
    if (dest.getType() != ChessType::Empty) return false;

    int rowMove = 0;
    int colMove = 0;

    if (initial.getColour() == ChessColour::White) {
        rowMove = initial.getCoords().getRow() - dest.getCoords().getRow();
        colMove = initial.getCoords().getColumn() - dest.getCoords().getColumn();
    }
    else if (initial.getColour() == ChessColour::Black) {
        rowMove = dest.getCoords().getRow() - initial.getCoords().getRow();
        colMove = dest.getCoords().getColumn() - initial.getCoords().getColumn();
    }
    return (rowMove == 2 && colMove == 0);
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
    whiteKing = other.whiteKing ? &board[other.whiteKing->getCoords().getRow()][other.whiteKing->getCoords().getColumn()] : nullptr;
    blackKing = other.blackKing ? &board[other.blackKing->getCoords().getRow()][other.blackKing->getCoords().getColumn()] : nullptr;
    // observers is not copied - only one board (the board use in chessGame) can have observers
}

ChessBoard &ChessBoard::operator=(const ChessBoard &other) {
    if (this == &other) return *this;
    board = other.board;
    whiteKing = other.whiteKing ? &board[other.whiteKing->getCoords().getRow()][other.whiteKing->getCoords().getColumn()] : nullptr;
    blackKing = other.blackKing ? &board[other.blackKing->getCoords().getRow()][other.blackKing->getCoords().getColumn()] : nullptr;
    return *this;
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

    if (pieceType == 'p' && r == 1) board[r][c].setMoved(false);
    else if (pieceType == 'P' && r == 6) board[r][c].setMoved(false);
    else board[r][c].setMoved(true);
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
    return validMove;
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

bool ChessBoard::isCastlingPossible(ChessSquare &initial, ChessSquare &dest, ChessColour turn) {
    int initial_row = initial.getRow();
    int initial_col = initial.getColumn();
    int dest_row = dest.getRow();
    int dest_col = dest.getColumn();

    // in order to initiate the castling, the chessSquare initial must occupy a king, dest muct occupy a rook
    // and they both must be the chessColour that correspond to the current game turn
    if (board[initial_row][initial_col].getColour() != turn) return false;
    if (board[dest_row][dest_col].getColour() != turn) return false;
    if (board[initial_row][initial_col].getType() != ChessType::King) return false;
    if (board[dest_row][dest_col].getType() != ChessType::Rook) return false;
    // if either king or rook has moved, castling is not possible
    if (board[initial_row][initial_col].hasMoved()) return false;
    if (board[dest_row][dest_col].hasMoved()) return false;

    // we now know that white king is at e1 ([7, 4]) / black king is at e8 ([0, 4])
    Rook r {turn, {dest_row, dest_col}};
    if (!isValidPath(dest, initial)) return false; // note that we evaluate path of the rook to the king, so (dest, initial)
    if (kingIsUnderAttack(turn)) return false;

    if (turn == ChessColour::White) {
        if (dest.getRow() == 7 && dest.getColumn() == 7) { // white castling to the right
            ChessBoard temp = *this;
            temp.chessMove(initial, {initial_row, initial_col+1});
            if (temp.kingIsUnderAttack(turn)) return false;
            temp.chessMove({initial_row, initial_col+1}, {initial_row, initial_col+2});
            if (temp.kingIsUnderAttack(turn)) return false;
        }
        else if (dest.getRow() == 7 && dest.getColumn() == 0) { // white castling to the left
            ChessBoard temp = *this;
            temp.chessMove(initial, {initial_row, initial_col-1});
            if (temp.kingIsUnderAttack(turn)) return false;
            temp.chessMove({initial_row, initial_col-1}, {initial_row, initial_col-2});
            if (temp.kingIsUnderAttack(turn)) return false;
        }
        else return false; // just for safety concern
    }
    else if (turn == ChessColour::Black) {
        if (dest.getRow() == 0 && dest.getColumn() == 7) { // black castling to the right
            ChessBoard temp = *this;
            temp.chessMove(initial, {initial_row, initial_col+1});
            if (temp.kingIsUnderAttack(turn)) return false;
            temp.chessMove({initial_row, initial_col+1}, {initial_row, initial_col+2});
            if (temp.kingIsUnderAttack(turn)) return false;
        }
        else if (dest.getRow() == 0 && dest.getColumn() == 0) { // black castling to the left
            ChessBoard temp = *this;
            temp.chessMove(initial, {initial_row, initial_col-1});
            if (temp.kingIsUnderAttack(turn)) return false;
            temp.chessMove({initial_row, initial_col-1}, {initial_row, initial_col-2});
            if (temp.kingIsUnderAttack(turn)) return false;
        }
        else return false;
    }
    return true;
}


bool ChessBoard::isEnPassantPossible(ChessSquare &initial, ChessSquare &dest, ChessColour turn, ChessMove &lastMove) {
    // to do en passant, the pawn must attempt to do a capturing move towards an empty space
    // assuming that we already deal with that in chessGame
    if (board[initial.getRow()][initial.getColumn()].getColour() != turn) return false;
    ChessColour opponent = (turn == ChessColour::White) ? ChessColour::Black : ChessColour::White;

    // if the piece we are attempting to capture is not an opponent pawn, it is invalid
    if (board[initial.getRow()][dest.getColumn()].getType() != ChessType::Pawn) return false;
    if (board[initial.getRow()][dest.getColumn()].getColour() != opponent) return false;

    // evaluate the last move from the opponent
    ChessPiece lastMovePiece = lastMove.getInitial();
    ChessPiece lastPieceFinalLocation = lastMove.getDest();

    // check if the last move from the opponent is a two square move pawn (has not moved previously), and it is the piece
    // that we want to capture
    if (lastMovePiece.getType() != ChessType::Pawn) return false;
    if (lastMovePiece.hasMoved()) return false;
    if (lastPieceFinalLocation.getCoords().getRow() != initial.getRow()) return false;
    if (lastPieceFinalLocation.getCoords().getColumn() != dest.getColumn()) return false;
    if (!pawnMoveTwoForward(lastMove)) return false;

    // if all requirements satisfy, en passant can be performed
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
    notifyObservers(board[currentRow][currentCol]);
    notifyObservers(board[finalRow][finalCol]);
}

/*
void ChessBoard::chessMoveCastling(ChessSquare king, ChessSquare rook) {
    // by isCastlingPossible function, we know that both king and rook has not moved, have same row, 
    // and have the same colour.
    // The castling only occur row-wise, so we only need to know which direction column (aka. the rook column) we need to take
    int king_r = king.getRow();
    int king_c = king.getColumn();
    int rook_r = rook.getRow();
    int rook_c = rook.getColumn();

    if (rook_c == 7) {
        ChessSquare new_king_location = {king_r, king_c+2};
        ChessSquare new_rook_location = {king_r, king_c+1};
        chessMove(king, new_king_location);
        chessMove(rook, new_rook_location);
    }
    else if (rook_c == 0) {
        ChessSquare new_king_location = {king_r, king_c-2};
        ChessSquare new_rook_location = {king_r, king_c-1};
        chessMove(king, new_king_location);
        chessMove(rook, new_rook_location);
    } 
}*/

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

vector<ChessMove> ChessBoard::PossibleMoveGenerator(ChessColour colour){
    std::vector<ChessPiece> allColourPieces;
    std::vector<ChessPiece> allMovablePieces;
    std::vector<ChessMove> allPossibleMoves;

    // first, get all the piece that have the colour of the player
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            if (board[r][c].getColour() == colour) allColourPieces.emplace_back(board[r][c]);
        }
    }

    // now, get all the pieces that have a valid move (validMoveExist)
    int length = allColourPieces.size();
    for (int i = 0; i < length; i++) {
        if (validMoveExist(allColourPieces[i].getCoords())) allMovablePieces.emplace_back(allColourPieces[i]);
    }

    // from the list of pieces that have valid move, get all possible moves from these pieces
    int numberOfPieces = allMovablePieces.size();
    for (int i = 0; i < numberOfPieces; ++i) {
        ChessSquare initial = allMovablePieces[i].getCoords();
        for (int r = 0; r < BOARD_DIMENSION; ++r) {
            for (int c = 0; c < BOARD_DIMENSION; ++c) {
                ChessSquare dest = board[r][c].getCoords();
                if (isValidMove(initial, dest, colour) && isValidPath(initial, dest)) {
                    ChessBoard temp = *this;
                    temp.chessMove(initial, dest);
                    if (!temp.kingIsUnderAttack(colour)) {
                        allPossibleMoves.emplace_back(ChessMove{allMovablePieces[i], board[r][c]});
                    }
                }
            }
        }
    }
    return allPossibleMoves;
}

// return a vector of Chesspiece of colour that under attack by the opponent
// this function can only avoid attack if it's our turn (colour turn)
vector<ChessPiece> ChessBoard::getUnderAttackPieces(ChessColour colour){
    vector<ChessPiece> result;
    vector<ChessPiece> pieceofColour;
    vector<ChessPiece> pieceofOpponent;
    ChessColour opponent = ChessColour::White; //will be updated later
    if (colour == ChessColour::White){
        opponent = ChessColour::Black;
    }
    // get the pieces of the given colour
    for (int r = 0; r < BOARD_DIMENSION; ++r){
        for (int c = 0; c < BOARD_DIMENSION; ++c){
            if (board[r][c].getColour() == colour){
                pieceofColour.emplace_back(board[r][c]);
            }
        }
    }
    // get the pieces of opponents
    for (int r = 0; r < BOARD_DIMENSION; ++r){
        for (int c = 0; c < BOARD_DIMENSION; ++c){
            if (board[r][c].getColour() == opponent){
                pieceofOpponent.emplace_back(board[r][c]);
            }
        }
    }
    int length = pieceofColour.size();
    int oppoLength = pieceofOpponent.size();
    for (int i = 0; i < length; ++i){
        if (validMoveExist(pieceofColour[i].getCoords())){
            for (int j = 0; j < oppoLength; ++j){
                ChessSquare target = pieceofColour[i].getCoords();
                ChessSquare oppo = pieceofOpponent[j].getCoords();
                if (isUnderAttack(target, oppo)){
                    // now the piece on pieceofColour[i] is underattack by the pieceofOpponent[j]
                    result.emplace_back(pieceofColour[i]);
                }
            }
        }
    }
    return result;

}

// get a vector of possible chessmove for single underattack piece that avoiding a capture
// this version of move doesn't guarantee that after moving is not under attack, just do a valid move if it's under attack
vector<ChessMove> ChessBoard::avoidAttackGenerator(ChessPiece p){
    vector <ChessMove>result;
    ChessSquare initial = p.getCoords();
    for (int r = 0; r < BOARD_DIMENSION; ++r) {
        for (int c = 0; c < BOARD_DIMENSION; ++c) {
            ChessSquare dest = board[r][c].getCoords();
            if (isValidMove(initial, dest, p.getColour()) && isValidPath(initial, dest)) {
                ChessBoard temp = *this;
                temp.chessMove(initial, dest);
                if (!temp.kingIsUnderAttack(p.getColour())) {
                    ChessMove temp {p, board[r][c]};
                    result.emplace_back(temp);
                }
            }
        }
    }
    return result;
}

bool ChessBoard::isCapturing(ChessMove move){
    // assuming that the move is already valid in terms of movement, path, and does not check current king
    ChessPiece attacking_piece = move.getInitial();
    ChessPiece under_attack_piece = move.getDest();
    if (attacking_piece.getColour() == ChessColour::White) {
        return (under_attack_piece.getColour() == ChessColour::Black);
    }
    else {
        return (under_attack_piece.getColour() == ChessColour::White);
    }
}

bool ChessBoard::isChecking(ChessMove move){
    // assuming that the move is already valid in terms of movement and path, and does not check the king
    ChessBoard temp = *this;
    temp.chessMove(move.getInitial().getCoords(), move.getDest().getCoords());
    ChessColour player = move.getInitial().getColour();
    ChessColour opponent = (player == ChessColour::White) ? ChessColour::Black : ChessColour::White;
    return temp.kingIsUnderAttack(opponent);
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

void ChessBoard::pawnPromotion(int row, int column, ChessColour colour, bool isHuman) {
    if (!isHuman) {
        board[row][column] = Queen{colour, {row, column}};
        notifyObservers(board[row][column]);
        return;
    }
    char pieceType;
    do {
        cin >> pieceType;
        if (cin.fail()) break;
        pieceType = toupper(pieceType);
        if (pieceType == 'Q') {
            board[row][column] = Queen{colour, {row, column}};
            notifyObservers(board[row][column]);
            break;
        }
        else if (pieceType == 'R') {
            board[row][column] = Rook{colour, {row, column}};
            notifyObservers(board[row][column]);
            break;
        }
        else if (pieceType == 'B') {
            board[row][column] = Bishop{colour, {row, column}};
            notifyObservers(board[row][column]);
            break;
        }
        else if (pieceType == 'N') {
            board[row][column] = Knight{colour, {row, column}};
            notifyObservers(board[row][column]);
            break;
        }
        else {
            cout << "Invalid promotion piece. Please enter again." << endl;
        }
    } while (true);
}






bool ChessBoard::pawnCapturingMove(ChessSquare &initial, ChessSquare &dest) {
    int pawn_row = initial.getRow();
    int pawn_col = initial.getColumn();
    int target_row = dest.getRow();
    int target_col = dest.getColumn();

    int rowMove = 0;
    int colMove = 0;

    ChessColour colour = board[pawn_row][pawn_col].getColour();
    if (colour == ChessColour::White) {
        rowMove = pawn_row - target_row;
        colMove = pawn_col - target_col;
    }
    else if (colour == ChessColour::Black) {
        rowMove = target_row - pawn_row;
        colMove = target_col - pawn_col;
    }
    if (rowMove != 1) return false;
    if (colMove != 1 && colMove != -1) return false;
    return true;
}

