
#pragma once 

#include <vector>
#include <string>
#include "Square.hpp"
#include "Move.hpp"


enum class Colors { Black = 0, White = 1 };

enum class PieceType { Pawn = 0, Knight, Bishop, Rook, Queen, King };

class Board;

class Piece {

    protected:
        Colors color_;
        PieceType type_;
        bool hasMoved_ { false };


    public:

        Piece(Colors color, PieceType type) : color_(color), type_(type) {};
        
        virtual ~Piece() = default; 

        // pure virtual function, every type of piece will have unique implementation 
        virtual std::vector<Move> getLegalMoves(const Board& board, Square position) const = 0; 
        virtual char getSymbol() const = 0;
        virtual std::string getUniCode() const = 0;

        Colors getColor() const { return color_;};
        PieceType getPieceType() const  { return type_; }
        bool isWhite() const { return color_ == Colors::White; };

        bool hasMoved() const { return hasMoved_; };
        void setMoved() { hasMoved_ = true; };


};