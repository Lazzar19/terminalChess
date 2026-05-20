
#include "Board.hpp"


constexpr int Board::squareFromFileAndRank(int file, int rank) {

    int square = file  + rank * 8;
    return square;
}

void  Board::fileAndRankFromSquare(int square, int& rank, int& file) {
    int rank  { square / 8 };
    int file { square % 8 };
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