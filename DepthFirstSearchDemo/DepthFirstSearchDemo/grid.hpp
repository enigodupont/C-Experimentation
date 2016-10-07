#pragma once
#include <sstream>

class grid {
public:
    grid(int totalRows = 0, int totalCols = 0, int sRow = 0, int sCol = 0, int eRow = 0, int eCol = 0){
            rows = totalRows;
            cols = totalCols;
            startRow = sRow;
            startCol = sCol;
            endRow = eRow;
            endCol = eCol;

    };

    bool inBounds(int row, int col) {
        return (row >= 0 & row < rows) & (col >= 0 & col < cols);
    }

    bool isEnd(int row, int col) {
        return (row == endRow) & (col == endCol);
    }

    std::string toString() {
        std::stringstream stream;
        stream << "(Row,Col) : " << "(" << rows << "," << cols << ")" << std::endl;
        stream << "(SRow,SCol) : " << "(" << startRow << "," << startCol << ")" << std::endl;
        stream << "(ERow,ECol) : " << "(" << endRow << "," << endCol << ")" << std::endl;

        return stream.str();
    }


    int startRow;
    int startCol;
private:
    int rows;
    int cols;
    int endRow;
    int endCol;
};