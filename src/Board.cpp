
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
    emptyBB =  ~occupiedBB;

    sideToMove = Colors::White;
    castlingRights = 0 ;
    enPassantSquare = -1;
    halfMoveClock = 0;
    fullMoveNumber = 1;

    historyOfMoves.clear();


}


constexpr int Board::squareFromFileAndRank(int file, int rank) {

    int square = file  + rank * 8;
    return square;
}

void  Board::fileAndRankFromSquare(int square, int& rank, int& file) const {
    rank =  square / 8;
    file =  square % 8;
}


bool Board::tryToSetPiece(int square, Colors color, PieceType type) {

    const U64 mask { squareMask(square) };

    // if there is already a piece on the square, we cannot set another one there
    if((occupiedBB & mask) != 0ULL) {
        return false;
    }

    const int index { pieceIndexFromColorAndType(color, type) };
    piecesBB[index] = setBit(piecesBB[index], square);
    updateOccupancy();

    return true;
}

void Board::forceSetPiece(int square, Colors color, PieceType type) {

    const int existingIndex { pieceIndexAt(square) };

    if(existingIndex != -1) { // if there is something already there, just clear it 
        piecesBB[existingIndex] = clearBit(piecesBB[existingIndex], square);
    }

    const int newIndex { pieceIndexFromColorAndType(color, type) };
    piecesBB[newIndex] = setBit(piecesBB[newIndex], square);
    updateOccupancy();

}


void Board::clearPieceFromSquare(int square) {

    
    const int index { pieceIndexAt(square) };
    
    if(index == -1) // there is no piece on the square 
        return; 

    piecesBB[index] = clearBit(piecesBB[index], square);
    updateOccupancy();

} 

void Board::updateOccupancy() {

    // from 12 separate boards we make one single "picture" of a table 
    
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


int Board::popCount(U64 bitboard) {

    // calculating how many pieces are on the board right now 

    int count { 0 };

    while(bitboard) {
        bitboard &= (bitboard - 1); // removes the least significant bit 
        ++count;
    }

    return count;
}

int Board::lsbIndex(U64 bitboard) {
    // least significant bit / index 
    if(bitboard == 0ULL)
        return -1;

    int index { 0 };

    while((bitboard & 1ULL) == 0ULL) {
        bitboard >>= 1;
        ++index;
    }

    return index;
}

int Board::popLSB(U64& bitboard) {
    // same as lsbIndex function, just removing lsb index 

    if(bitboard == 0ULL)
        return -1;

    int index { lsbIndex(bitboard) };

    bitboard &= (bitboard - 1);
    return index;

}

int Board::pieceIndexAt(int square) const  {

    for(int i { 0 }; i < 12; ++i) {

        if((piecesBB[i] & squareMask(square)) != 0ULL) {
            return i; // just returning the index of occupied piece 
        }

    }

    return -1; // -1 by default for convention 
}