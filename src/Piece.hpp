
#pragma once 

#include <vector>
#include <string>
#include "Square.hpp"
#include "Move.hpp"


enum class Colors { Black, White };

enum class PieceType { Pawn, Knight, Bishop, Rook, Queen, King };

class Board;

class Piece {

    protected:
        Colors color_;
        PieceType type_;
        bool hasMoved_;


    public:

        Piece(Colors color, PieceType type) : color_(color), type_(type), hasMoved_(false) {};
        
        virtual ~Piece() = default;

        virtual std::vector<Move> getLegalMoves(const Board& board, Square position) const = 0; 
        virtual char getSymbol() const = 0;
        virtual std::string getUniCode() const = 0;

        Colors getColor() { return color_;};
        PieceType getPieceType() { return type_; }
        bool isWhite() const { return color_ == Colors::White; };

        bool hasMoved() const { return hasMoved_; };
        void setMoved() { hasMoved_ = true; };


};