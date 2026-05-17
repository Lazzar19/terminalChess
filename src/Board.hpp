

#pragma once 

#include <array>
#include <memory> 
#include <cstdint>

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
        virtual ~Board() = default;



};

