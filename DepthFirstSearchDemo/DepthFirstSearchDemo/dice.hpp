#pragma once
#include <sstream>
enum dieValue {
    one,
    two,
    three,
    four,
    five,
    six
};
enum direction {
    up,
    down,
    left,
    right,
    done
};

class dice {
public:
    dice(int startRow = 0, int startCol = 0, dieValue startVal = one) {
        currentRow = startRow;
        currentCol = startCol;
        currentValue = startVal;
    }
    void moveDirection(direction dir) {
        switch (dir) {
            case up:
                moveUp();
                break;
            case down:
                moveDown();
                break;
            case left:
                moveLeft();
                break;
            case right:
                moveRight();
                break;
        }
    }
    int getCurrentCol() {
        return currentCol;
    }
    int getCurrentRow() {
        return currentRow;
    }
    dieValue getCurrentValue() {
        return currentValue;
    }

    std::string toString() {
        std::stringstream stream;
        stream << "(Row,Col) : " << "(" << currentRow << "," << currentCol << ") ";
        stream << "Facing Value : " << currentValue + 1 << std::endl;

        return stream.str();
    }
private:
    dieValue currentValue;
    int currentCol;
    int currentRow;

    void moveUp() {
        switch (currentValue) {
            case one:
                currentValue = two;
                break;
            case two:
                currentValue = six;
                break;
            case three:
                currentValue = two;
                break;
            case four:
                currentValue = two;
                break;
            case five:
                currentValue = one;
                break;
            case six:
                currentValue = five;
                break;
            }
            currentRow--;
        }
        void moveDown() {
            switch (currentValue) {
            case one:
                currentValue = five;
                break;
            case two:
                currentValue = one;
                break;
            case three:
                currentValue = five;
                break;
            case four:
                currentValue = five;
                break;
            case five:
                currentValue = six;
                break;
            case six:
                currentValue = two;
                break;
            }
            currentRow++;
        }
        void moveLeft() {
            switch (currentValue) {
            case one:
                currentValue = four;
                break;
            case two:
                currentValue = four;
                break;
            case three:
                currentValue = five;
                break;
            case four:
                currentValue = six;
                break;
            case five:
                currentValue = four;
                break;
            case six:
                currentValue = three;
                break;
            }
            currentCol--;
        }
        void moveRight() {
            switch (currentValue) {
            case one:
                currentValue = three;
                break;
            case two:
                currentValue = three;
                break;
            case three:
                currentValue = six;
                break;
            case four:
                currentValue = six;
                break;
            case five:
                currentValue = four;
                break;
            case six:
                currentValue = three;
                break;
            }
            currentCol++;
        }
};