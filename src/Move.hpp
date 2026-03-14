
#pragma once 

#include "Square.hpp"


enum class PossibleMoves {

    NormalMove,
    Castling,
    Promotion,
    EnPassant
    
};

struct Move {

    Square from;
    Square to;
    PossibleMoves type { PossibleMoves::NormalMove };

};