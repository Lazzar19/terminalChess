
#include "Board.hpp"

Board::Board() {
    clearBoard();
}


void Board::clearBoard() {

    for(U64& board :  piecesBB)
        board = 0ULL;

    occupiedBB = 0ULL;
    whitePiecesBB = 0ULL;
    blackPiecesBB = 0ULL;
    emptyBB = 0ULL;

    sideToMove = Colors::White;
    castlingRights = 0 ;
    enPassantSquare = -1;
    halfMoveClock = 0;
    fullMoveNumber = 1;

    
}


constexpr int Board::squareFromFileAndRank(int file, int rank) {

    int square = file  + rank * 8;
    return square;
}

void  Board::fileAndRankFromSquare(int square, int& rank, int& file) const {
    rank =  square / 8;
    file =  square % 8;
}

void Board::setPiece(int square, Colors color, PieceType type) {

    // square is calculated before calling setPiece
    // it doesnt matter is it calculated from rank and file or from bitmap 

    int index { pieceIndexFromColorAndType(color, type) };
    piecesBB[index] = setBit(piecesBB[index], square); // setting piece using index 
    updateOccupancy(); 

}

void Board::removePiece(int square, Colors color, PieceType type) {

    // same here with square 

    int index { pieceIndexFromColorAndType(color, type) };
    piecesBB[index] = clearBit(piecesBB[index], square);

    updateOccupancy();
}

void Board::updateOccupancy() {

    // from 12 separate boards we make one single "picture" of table 
    
    whitePiecesBB = 0ULL;
    blackPiecesBB = 0ULL;

    for(int i { 0 }; i < 6; ++i) {
        blackPiecesBB |= piecesBB[i];
    }

    for(int i { 6 }; i < 12; ++i) {
        whitePiecesBB |= piecesBB[i];
    }

    occupiedBB = whitePiecesBB | blackPiecesBB;
    emptyBB = ~occupiedBB;

}