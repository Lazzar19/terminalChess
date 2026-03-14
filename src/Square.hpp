
#include <string>

#pragma once 


struct Square {

    int row {};
    int col {};

    bool isValidState() const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }

    bool operator==(const Square& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Square& other) const {
        return !(other == *this);
    }

    std::string toChessBoardNotation() {

        // std::string(4, '-') gives "----" 

        return std::string(1, 'a' + col) + std::to_string(row + 1); 
    }
};