//
// Created by tijsh on 2-1-2022.
//

#include "ProgressMeasuresAlgo.h"
#include "FixedOrdering.h"

#include "Node.h"


#include <limits>
#include <iostream>
#include <chrono>
#include <algorithm>
#include "ImprovedWorkingListOrderer.h"
#include "WorkingListOrderer.h"
#include "Orderer.h"

void ProgressMeasuresAlgo::solveParityGameInputOrder(ParityGame &parityGame,
                                                   std::unordered_map<int, ProgressMeasure> &rhoMapping) {
    auto nodes = parityGame.getNodes();
    auto order = FixedOrdering::inputOrder(nodes);

    solveParityGameForOrder(parityGame, rhoMapping, order);
}

void ProgressMeasuresAlgo::solveParityGameRandomOrder(ParityGame &parityGame,
                                                      std::unordered_map<int, ProgressMeasure> &rhoMapping) {
    auto nodes = parityGame.getNodes();
    auto order = FixedOrdering::randomOrder(nodes);

    solveParityGameForOrder(parityGame, rhoMapping, order);
}

void ProgressMeasuresAlgo::solveParityGameEvenOddOrder(ParityGame &parityGame,
                                                      std::unordered_map<int, ProgressMeasure> &rhoMapping, bool even) {
    auto nodes = parityGame.getNodes();
    auto order = FixedOrdering::evenOddOrder(nodes, even);

    solveParityGameForOrder(parityGame, rhoMapping, order);
}

void ProgressMeasuresAlgo::solveParityGameOwnerOrder(ParityGame &parityGame,
                                                       std::unordered_map<int, ProgressMeasure> &rhoMapping, bool owner) {
    auto nodes = parityGame.getNodes();
    auto order = FixedOrdering::ownerOrder(nodes, owner);

    solveParityGameForOrder(parityGame, rhoMapping, order);
}

void ProgressMeasuresAlgo::solveParityGamePriorityOrder(ParityGame &parityGame,
                                                       std::unordered_map<int, ProgressMeasure> &rhoMapping, bool highLow) {
    auto order = FixedOrdering::priorityOrder(parityGame, highLow);

    solveParityGameForOrder(parityGame, rhoMapping, order);
}

void ProgressMeasuresAlgo::solveParityGameEvenOddPriorityOrder(ParityGame &parityGame,
                                                        std::unordered_map<int, ProgressMeasure> &rhoMapping, bool even, bool highLow) {
    auto order = FixedOrdering::evenOddPriorityOrder(parityGame, even, highLow);

    solveParityGameForOrder(parityGame, rhoMapping, order);
}

void ProgressMeasuresAlgo::solveParityGameOwnerPriorityOrder(ParityGame &parityGame,
                                                        std::unordered_map<int, ProgressMeasure> &rhoMapping, bool diamond, bool highLow) {
    auto order = FixedOrdering::ownerPriorityOrder(parityGame, diamond, highLow);

    solveParityGameForOrder(parityGame, rhoMapping, order);
}

void ProgressMeasuresAlgo::solveParityGameWorkList(ParityGame &parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping) {
    WorkingListOrderer workingList;
    for(const auto& node : parityGame.getNodes()) {
        workingList.addNode(node);
    }
    solveParityGameUsingWorkList(parityGame, rhoMapping, workingList);

}

void ProgressMeasuresAlgo::solveParityGameImprovedWorkList(ParityGame &parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping) {



    ImprovedWorkingListOrderer workingList;
    for(const auto& node : parityGame.getNodes()) {
        workingList.addNode(node);
    }
    solveParityGameUsingWorkList(parityGame, rhoMapping, workingList);

}


ProgressMeasure
ProgressMeasuresAlgo::Prog(const std::unordered_map<int, ProgressMeasure> &rhoMapping, const Node &v, const Node &w, const ParityGame &parityGame) {

    std::vector<int> leastVector(parityGame.getDValue());

    auto rhoForW = rhoMapping.at(w.getId());

    // Priority of v is even
    if(v.hasEvenPriority()) {
        // only top >= top
        if(rhoForW.isTop()) {
            return rhoForW;
        } else {
            return rhoForW.getEvenProg(v.getPriority());
        }

    } else { // priority of v is odd
        // only top > top
        if(rhoForW.isTop()) {
            return rhoForW;
        } else {
            return rhoForW.getOddProg(v.getPriority());
        }
    }
}

bool ProgressMeasuresAlgo::lift(const Node &v, std::unordered_map<int, ProgressMeasure>& rhoMapping, const ParityGame &parityGame) {

    auto& successors = v.getSuccessors();

    std::vector<ProgressMeasure> progMeasures;
    progMeasures.reserve(successors.size());
    for (const auto& w : successors) {
        progMeasures.push_back(Prog(rhoMapping, v, *w, parityGame));
    }

    if(v.isDiamond()) {
        ProgressMeasure minElement = *std::min_element(progMeasures.begin(), progMeasures.end());
        auto updatedProgressMeasure = std::max(rhoMapping.at(v.getId()), minElement);
        if(rhoMapping[v.getId()] == updatedProgressMeasure) {
            return false;
        } else {
            rhoMapping[v.getId()] = updatedProgressMeasure;
            return true;
        }


    } else { // v is box
        ProgressMeasure maxElement = *std::max_element(progMeasures.begin(), progMeasures.end());

        auto updatedProgressMeasure = std::max(rhoMapping.at(v.getId()), maxElement);

        if(rhoMapping[v.getId()] == updatedProgressMeasure) {
            return false;
        } else {
            rhoMapping[v.getId()] = updatedProgressMeasure;
            return true;
        }
    }

}

void ProgressMeasuresAlgo::printVectorElements(const std::vector<std::shared_ptr<Node>> nodes) {
    for (auto i = 0; i < nodes.size(); i++) {
        std::cout << nodes.at(i)->getId() << "; ";
    }
    std::cout << std::endl;
}


void ProgressMeasuresAlgo::solveParityGameForOrder(ParityGame &parityGame, std::unordered_map<int, ProgressMeasure>& rhoMapping, std::vector<std::shared_ptr<Node>> order) {
    bool madeUpdate = true;
    while(madeUpdate) {
        madeUpdate = false;
        for(const auto& node : order) {
            bool lifted = lift(*node, rhoMapping, parityGame);
            if(lifted) {
                madeUpdate = true;
            }
        }
    }

}


void ProgressMeasuresAlgo::solveParityGameUsingWorkList(ParityGame &parityGame,
                                                        std::unordered_map<int, ProgressMeasure> &rhoMapping,
                                                        Orderer &workList) {

    auto start = std::chrono::high_resolution_clock::now();
    while(!workList.isEmpty()) {
        const auto node = workList.popFront();
        // On top no lifting needs to be done
        if(rhoMapping.at(node->getId()).isTop()) {continue;}



        bool lifted = improvedLift(*node, rhoMapping, parityGame);


        if(lifted) {
            for(const auto& predecessor : node->getPredecessors()) {
                workList.addNode(predecessor);
            }
        }
        //continue lifting until stability is reached..
        while(lifted) {
            lifted = improvedLift(*node, rhoMapping, parityGame);
        }

    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
//    std::cout << "solveParityGame exec time: " << microseconds << std::endl;

}

bool ProgressMeasuresAlgo::improvedLift(const Node &v, std::unordered_map<int, ProgressMeasure> &rhoMapping,
                                        const ParityGame &parityGame) {
    // Top won't be lifted further so we can immediately return that no update has been done.
    if(rhoMapping.at(v.getId()).isTop()) {return false;}

    // Not yet top
    // When it's level1 node we can immediately set it top. Return true since it was not yet top.
    bool vIsLevel1Node = (v.isSquare() && v.hasOddPriority() && v.hasSelfLoop())
            || (v.isDiamond() && v.hasOddPriority() && v.hasSelfLoop() && v.hasOnlySingleSuccessor());
    if(vIsLevel1Node) {
        rhoMapping[v.getId()] = rhoMapping[v.getId()].getTop();
        return true;
    } else {
        return lift(v, rhoMapping, parityGame);
    }

}



