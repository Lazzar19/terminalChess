

#pragma once 

#include <cstdint>
#include <vector>

#include "Piece.hpp"
#include "Move.hpp"

using U64 = uint64_t;


class Board {

    public:

        enum PieceIndex : int {
            wPAWN = 0,
            wKNIGHT, // 1
            wBISHOP, // 2 
            wROOK, // 3 
            wQUEEN, // 4 
            wKING, // 5 
            bPAWN, // 6
            bKNIGHT, // 7 
            bBISHOP, // 8 
            bROOK, // 9 
            bQUEEN, // 10
            bKING // 11s
        };

        static constexpr int pieceIndexFromColorAndType(Colors color, PieceType type) {
            // white pieces are represented as 1 and black as 0 
            const int colorIndex  { (color == Colors::White) ? 1 : 0 };
            return colorIndex * 6 + static_cast<int>(type);
        }

        static constexpr Colors colorFromPieceIndex(int index) {
            return index < 6 ? Colors::Black : Colors::White;
        }

        static constexpr PieceType pieceTypeFromPieceIndex(int index) {
            return static_cast<PieceType>(index % 6);
        }

    private: 
        

        U64 piecesBB[14]; // bitmap for every piece type and color
        U64 occupiedBB;
        U64 whitePiecesBB;
        U64 blackPiecesBB;
        U64 emptyBB;

        Colors sideToMove { Colors::White };
        uint8_t castlingRights { 0 }; 
        int8_t enPassantSquare { -1 }; // -1 means none 
        int halfMoveClock { 0 };
        int fullMoveNumber { 1 };

        struct Undo {

            uint8_t indexOfCapturedPiece;
            uint8_t castlingRights;
            int8_t enPassantSquare;
            int halfMoveClock;
            U64 movedFromToMask;

        };

        std::vector<Undo> historyOfMoves;

    public:
        
        Board();

        static inline U64 squareMask(int square) {
            return 1ULL << square;
        }

        static inline U64 setBit(U64 bb, int target) {
            return bb | (1ULL << target);
        }

        static inline U64 clearBit(U64 bb, int target)
        {
            return bb & ~(1ULL << target);
        }

        static constexpr int squareFromFileAndRank(int file, int rank);
        void fileAndRankFromSquare(int square, int& file, int& rank);


        void clearBoard();
        void setPiece(int square, Colors color, PieceType type);
        void removePiece(int square, Colors color, PieceType type);
        int pieceIndexAt(int square) const;




        void updateOccupancy();
        static int popCount(U64 bb);
        static int lsbIndex(U64 bb);
        static int popLSB(U64& bb);




};

