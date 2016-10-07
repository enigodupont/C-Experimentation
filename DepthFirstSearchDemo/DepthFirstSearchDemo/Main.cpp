#include <iostream>
#include <vector>

#include "dice.hpp"
#include "grid.hpp"
#include "utility.hpp"
#define debug true

int main(int argc, char** argv) {
    
    
    grid myGrid = readGridInformationFromFile("test1.txt");

    if (debug) {
        std::cout << myGrid.toString() << std::endl;
    }

    dice myDie(myGrid.startRow,myGrid.startCol,one);
    
    auto bestPath = traverseGrid(myGrid,myDie);

    for (int i = 0; i < bestPath.path.size(); i++) {
        std::cout << bestPath.path[i].diceStatus.toString() << std::endl;
    }
    std::cout << "Total Value: " << bestPath.getTotal() << std::endl;

    return 0;
}