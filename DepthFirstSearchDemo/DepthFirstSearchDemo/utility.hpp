#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "dice.hpp"
#include "grid.hpp"

grid readGridInformationFromFile(std::string fileName) {
    std::ifstream inputFile;

    inputFile.open(fileName.c_str());

    if(!inputFile.is_open()){
        std::cerr << "File could not be opened! Check " << fileName << std::endl;
        std::exit(-1);
    }

    int rows, cols, sRow, sCol, eRow, eCol;

    inputFile >> rows >> cols >> sRow >> sCol >> eRow >> eCol;

    return grid(rows,cols,sRow,sCol,eRow,eCol);

}

struct spotStatus {
    dice diceStatus;
    direction currentDirection = up;
};

struct traversalStats {
    std::vector<spotStatus> path;
    
    int getTotal() {
        int total = 0;
        for (int i = 0; i < path.size(); i++) {
            total += path[i].diceStatus.getCurrentValue() + 1;
        }
        return total;
    }
};


traversalStats traverseGrid(grid myGrid, dice die) {
    std::vector<spotStatus> depthFirstTraversal;
    std::vector<traversalStats> traversalHistory;

    spotStatus initStatus;
    initStatus.diceStatus = die;
    initStatus.currentDirection = up;

    depthFirstTraversal.push_back(initStatus);

    while (depthFirstTraversal.size() > 0) {

        spotStatus newStatus;
        newStatus.diceStatus = depthFirstTraversal.back().diceStatus;

        switch (depthFirstTraversal.back().currentDirection) {
            case up:
                newStatus.diceStatus.moveDirection(up);
                depthFirstTraversal.back().currentDirection = right;
                break;
            case right:
                newStatus.diceStatus.moveDirection(right);
                depthFirstTraversal.back().currentDirection = down;
                break;
            case down:
                newStatus.diceStatus.moveDirection(down);
                depthFirstTraversal.back().currentDirection = left;
                break;
            case left:
                newStatus.diceStatus.moveDirection(left);
                depthFirstTraversal.back().currentDirection = done;
                break;
            case done:
                depthFirstTraversal.pop_back();
                continue;
                break;
        }
        
        bool alreadyVisited = false;
        //Check if newStatus position is in the traversal already
        for (int i = 0; i < depthFirstTraversal.size(); i++) {
            if ((depthFirstTraversal[i].diceStatus.getCurrentCol() == newStatus.diceStatus.getCurrentCol()) & (depthFirstTraversal[i].diceStatus.getCurrentRow() == newStatus.diceStatus.getCurrentRow())) {
                alreadyVisited = true;
                break;
            }
        }

        if (myGrid.inBounds(newStatus.diceStatus.getCurrentRow(), newStatus.diceStatus.getCurrentCol()) && !alreadyVisited) {
            depthFirstTraversal.push_back(newStatus);

            if (myGrid.isEnd(newStatus.diceStatus.getCurrentRow(), newStatus.diceStatus.getCurrentCol())) {
                traversalStats newStat;
                newStat.path = depthFirstTraversal;
                traversalHistory.push_back(newStat);
                depthFirstTraversal.pop_back();
            }
        }

    }


    
    traversalStats bestStats = traversalHistory[0];
    for (int i = 1; i < traversalHistory.size(); i++) {
        if (bestStats.getTotal() > traversalHistory[i].getTotal()) {
            bestStats = traversalHistory[i];
        }
    }
    
    return bestStats;
    
}
